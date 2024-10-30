#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct stack_node {
  int payload;
  struct stack_node* prev;
} stack_node_t;

typedef struct lf_mpsc_stack {
  struct stack_node* _Atomic top;
} lf_mpsc_stack_t;

void stack_init(lf_mpsc_stack_t* stack) {
  stack->top = NULL;
}

void stack_destroy(lf_mpsc_stack_t* stack) {
  stack_node_t* curr = stack->top;
  while (curr != NULL) {
    stack_node_t* prev = curr->prev;
    free(curr);
    curr = prev;
  }
}

void stack_push(lf_mpsc_stack_t* stack, int value) {
  // ???
}

stack_node_t* stack_pop(lf_mpsc_stack_t* stack) {
  // ???
}

//////////////////////////////////////////////////////////////////////

const int n_pushes = 100500;

void* producer(void* arg) {
  lf_mpsc_stack_t* stack = (lf_mpsc_stack_t*)arg;
  for (int i = 0; i < n_pushes; ++i) {
    stack_push(stack, i);
  }

  return NULL;
}

void* consumer(void* arg) {
  lf_mpsc_stack_t* stack = (lf_mpsc_stack_t*)arg;
  for (int i = 0; i < n_pushes; ++i) {
    stack_node_t* node;
    while ((node = stack_pop(stack)) == NULL) {
      // Retry...
    }

    printf("got: %d\n", node->payload);
    free(node);
  }

  return NULL;
}

int main() {
  lf_mpsc_stack_t stack;
  stack_init(&stack);

  pthread_t p;
  pthread_create(&p, /*attr=*/NULL, &producer, /*arg=*/&stack);
  pthread_t c;
  pthread_create(&c, /*attr=*/NULL, &consumer, /*arg=*/&stack);

  pthread_join(p, /*thread_return=*/NULL);
  pthread_join(c, /*thread_return=*/NULL);

  stack_destroy(&stack);
  return 0;
}
