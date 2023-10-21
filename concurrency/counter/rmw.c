#include <stdio.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>

// typedef int64_t atomic_int64_t;
typedef atomic_int_fast64_t atomic_int64_t;

atomic_int64_t counter = 0;

void* add_10k(void* arg) {
  atomic_int64_t* counter_ptr = (atomic_int64_t*)arg;
  for (int i = 0; i < 10000; ++i) {
    atomic_fetch_add(counter_ptr, 1);
  }

  return NULL;
}

int main() {
  const size_t n_threads = 4;

  pthread_t threads[n_threads];
  for (size_t i = 0; i < n_threads; ++i) {
    pthread_create(&threads[i], /*attr=*/NULL, &add_10k, &counter);
  }

  for (size_t i = 0; i < n_threads; ++i) {
    pthread_join(threads[i], /*thread_return=*/NULL);
  }

  printf("counter = %ld\n", counter);
  return 0;
}
