#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

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
  node->prev = list->head;
  node->next = NULL;

  if (list->size > 0) {
    list->head->next = node;
    list->head = node;
  } else {
    list->head = node;
    list->tail = node;
  }

  ++list->size;
}

void list_push_front(list_t* list, int value) {
  list_node_t* node = malloc(sizeof(list_node_t));
  node->payload = value;
  node->prev = NULL;
  node->next = list->tail;

  if (list->size > 0) {
    list->tail->prev = node;
    list->tail = node;
  } else {
    list->head = node;
    list->tail = node;
  }

  ++list->size;
}

int main() {
  list_t list;
  list_init(&list);

  for (size_t i = 0; i < 10; ++i) {
    list_push_front(&list, i);
    list_push_back(&list, i);
  }

  list_node_t* curr = list.tail;
  while (curr != NULL) {
    printf("%d ", curr->payload);
    curr = curr->next;
  }

  list_destroy(&list);
  return 0;
}
