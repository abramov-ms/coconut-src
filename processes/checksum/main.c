#include <err.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define verify(expr)                               \
  if (!(expr)) {                                   \
    err(EXIT_FAILURE, "assertion failed: " #expr); \
  }

typedef struct {
  const uint8_t* bytes;
  size_t size;
} sum_args_t;

void* sum(void* ptr) {
  uint8_t sum = 0;
  sum_args_t* args = (sum_args_t*)ptr;
  for (size_t i = 0; i < args->size; ++i) {
    sum += args->bytes[i];
  }

  return (void*)(uint64_t)sum;
}

uint8_t checksum(int fd, size_t n_jobs) {
  struct stat stbuf = {};
  verify(fstat(fd, &stbuf) == 0);
  size_t size = stbuf.st_size;

  const uint8_t* bytes;
  verify((bytes = (const uint8_t*)mmap(/*addr=*/NULL, size, PROT_READ,
                                       MAP_PRIVATE, fd,
                                       /*offset=*/0)) != NULL);
  size_t part_size = size / n_jobs;
  size_t remainder_size = size % n_jobs;
  pthread_t* workers = malloc(n_jobs * sizeof(pthread_t));
  sum_args_t* args = malloc(n_jobs * sizeof(sum_args_t));
  for (size_t j = 0; j < n_jobs; ++j) {
    args[j].bytes = bytes + j * part_size;
    args[j].size = part_size + remainder_size * (j + 1 == n_jobs);
    pthread_create(&workers[j], /*attr=*/NULL, &sum, &args[j]);
  }

  uint8_t sum = 0;
  for (size_t j = 0; j < n_jobs; ++j) {
    void* part_sum;
    pthread_join(workers[j], &part_sum);
    sum += (uint8_t)(uint64_t)part_sum;
  }

  free(workers);
  free(args);

  verify(munmap((void*)bytes, size) == 0);
  return sum;
}

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    printf("usage: %s FILEPATH\n", argv[0]);
    return EXIT_FAILURE;
  }

  int fd;
  if ((fd = open(argv[1], O_RDONLY)) == -1) {
    err(EXIT_FAILURE, "failed to open %s\n", argv[1]);
  }

  const size_t n_jobs = 1;
  printf("%hhu\n", checksum(fd, n_jobs));
  return 0;
}
