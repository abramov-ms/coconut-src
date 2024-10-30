#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

//  push              pop
// ----------------------->
// [node][node][node][node]
//  ^^^^              ^^^^
//  tail              head

typedef struct queue_node {
  char* message;
  struct queue_node* prev;
  struct queue_node* next;
} queue_node_t;

typedef struct mpmc_queue {
  size_t size;
  bool closed;
  queue_node_t* tail;
  queue_node_t* head;
  pthread_mutex_t mutex;
  pthread_cond_t has_message;
} mpmc_queue_t;

void queue_init(mpmc_queue_t* queue) {
  queue->size = 0;
  queue->closed = false;
  queue->head = NULL;
  queue->tail = NULL;
  pthread_mutex_init(&queue->mutex, /*attr=*/NULL);
  pthread_cond_init(&queue->has_message, /*attr=*/NULL);
}

void queue_destroy(mpmc_queue_t* queue) {
  assert(queue->closed);
  pthread_cond_destroy(&queue->has_message);
  pthread_mutex_destroy(&queue->mutex);
  queue_node_t* curr = queue->tail;
  while (curr != NULL) {
    queue_node_t* next = curr->next;
    free(curr->message);
    free(curr);
    curr = next;
  }
}

void queue_close(mpmc_queue_t* queue) {
  pthread_mutex_lock(&queue->mutex);
  queue->closed = true;
  pthread_cond_broadcast(&queue->has_message);
  pthread_mutex_unlock(&queue->mutex);
}

void queue_push(mpmc_queue_t* queue, char* message) {
  queue_node_t* node = malloc(sizeof(queue_node_t));
  node->message = message;
  node->prev = NULL;

  pthread_mutex_lock(&queue->mutex);

  node->next = queue->tail;
  if (queue->size > 0) {
    queue->tail->prev = node;
    queue->tail = node;
  } else {
    queue->head = node;
    queue->tail = node;
  }
  ++queue->size;

  pthread_cond_signal(&queue->has_message);
  pthread_mutex_unlock(&queue->mutex);
}

char* queue_pop(mpmc_queue_t* queue) {
  pthread_mutex_lock(&queue->mutex);
  while (queue->size == 0 && !queue->closed) {
    // 1. unlock
    // 2. sleep
    pthread_cond_wait(&queue->has_message, &queue->mutex);
  }

  char* message;
  if (queue->closed) {
    message = NULL;
    goto out;
  }

  queue_node_t* head = queue->head;
  if (queue->size > 1) {
    queue->head = queue->head->prev;
    queue->head->next = NULL;
  } else {
    queue->head = NULL;
    queue->tail = NULL;
  }
  message = head->message;
  free(head);
  --queue->size;

out:
  pthread_mutex_unlock(&queue->mutex);
  return message;
}

//////////////////////////////////////////////////////////////////////

const int n_messages = 10;
const useconds_t sleep_useconds = 500000;

void* producer(void* arg) {
  mpmc_queue_t* queue = (mpmc_queue_t*)arg;

  for (size_t i = 0; i < n_messages; ++i) {
    char* message = malloc(128);
    sprintf(message, "ping #%lu", i);
    queue_push(queue, message);
    usleep(sleep_useconds);
  }

  queue_close(queue);
  return NULL;
}

void* consumer(void* arg) {
  mpmc_queue_t* queue = (mpmc_queue_t*)arg;

  char* message;
  while ((message = queue_pop(queue)) != NULL) {
    printf("got: %s\n", message);
    free(message);
  }

  return NULL;
}

//////////////////////////////////////////////////////////////////////

int main() {
  mpmc_queue_t queue;
  queue_init(&queue);

  pthread_t p;
  pthread_create(&p, /*attr=*/NULL, &producer, &queue);
  pthread_t c;
  pthread_create(&c, /*attr=*/NULL, &consumer, &queue);

  pthread_join(p, /*thread_return=*/NULL);
  pthread_join(c, /*thread_return=*/NULL);

  queue_destroy(&queue);

  return 0;
}
