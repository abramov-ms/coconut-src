#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>

atomic_bool locked = false;

// void lock() {
//   while (atomic_exchange(&locked, true)) {
//     // Backoff...
//   }
// }

void lock() {
  while (atomic_exchange(&locked, true)) {
    while (atomic_load(&locked)) {
      // Backoff...
    }
  }
}

void unlock() {
  atomic_store(&locked, false);
}

//////////////////////////////////////////////////////////////////////

//  front             back
// ----------------------->
// [node][node][node][node]
//  ^^^^              ^^^^
//  tail              head

typedef struct list_node {
  int payload;
  struct list_node* prev;
  struct list_node* next;
} list_node_t;

typedef struct list {
  size_t size;
  list_node_t* head;
  list_node_t* tail;
} list_t;

void list_init(list_t* list) {
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
}

void list_destroy(list_t* list) {
  list_node_t* curr = list->tail;
  while (curr != NULL) {
    list_node_t* next = curr->next;
    free(curr);
    curr = next;
  }
}

void list_push_back(list_t* list, int value) {
  list_node_t* node = malloc(sizeof(list_node_t));
  node->payload = value;
  node->next = NULL;

  lock();

  node->prev = list->head;
  if (list->size > 0) {
    list->head->next = node;
    list->head = node;
  } else {
    list->head = node;
    list->tail = node;
  }
  ++list->size;

  unlock();
}

void list_push_front(list_t* list, int value) {
  list_node_t* node = malloc(sizeof(list_node_t));
  node->payload = value;
  node->prev = NULL;

  lock();

  node->next = list->tail;
  if (list->size > 0) {
    list->tail->prev = node;
    list->tail = node;
  } else {
    list->head = node;
    list->tail = node;
  }
  ++list->size;

  unlock();
}

//////////////////////////////////////////////////////////////////////

const int64_t n_threads = 4;
const int64_t n_end_pushes = 1000;

void* push_both_ends(void* arg) {
  list_t* list = (list_t*)arg;
  for (int64_t i = 0; i < n_end_pushes; ++i) {
    list_push_front(list, i);
    list_push_back(list, i);
  }

  return NULL;
}

int main() {
  list_t list;
  list_init(&list);

  pthread_t threads[n_threads];
  for (int64_t i = 0; i < n_threads; ++i) {
    pthread_create(&threads[i], /*attr=*/NULL, &push_both_ends, &list);
  }
  for (int64_t i = 0; i < n_threads; ++i) {
    pthread_join(threads[i], /*thread_return=*/NULL);
  }

  int64_t sum = 0;
  list_node_t* curr = list.tail;
  while (curr != NULL) {
    sum += curr->payload;
    curr = curr->next;
  }

  list_destroy(&list);

  printf("expected_sum = %ld\n", n_threads * n_end_pushes * (n_end_pushes - 1));
  printf("actual_sum = %ld\n", sum);

  return 0;
}
