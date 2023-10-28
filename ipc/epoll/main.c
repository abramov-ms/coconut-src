#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

ssize_t read_all(int fd, char buf[], size_t count) {
  size_t done = 0;
  while (done < count) {
    ssize_t bytes = read(fd, buf + done, count - done);
    if (bytes < 0) {
      return bytes;
    } else if (bytes == 0) {
      break;
    }

    done += bytes;
  }

  return done;
}

ssize_t write_all(int fd, char buf[], size_t count) {
  size_t done = 0;
  while (done < count) {
    ssize_t bytes = write(fd, buf + done, count - done);
    if (bytes < 0) {
      return bytes;
    }

    done += bytes;
  }

  return done;
}

int main(int argc, const char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s FIFO [FIFO...]", argv[0]);
    return EXIT_FAILURE;
  }

  int n_fifos = argc - 1;
  const char** fifos = argv + 1;
  int fds[n_fifos];
  for (int i = 0; i < n_fifos; ++i) {
    if ((fds[i] = open(fifos[i], O_RDONLY)) == -1) {
      err(EXIT_FAILURE, "open %s", fifos[i]);
    }
  }

  int epoll;
  if ((epoll = epoll_create(/*flags=*/0)) == -1) {
    err(EXIT_FAILURE, "epoll_create1");
  }

  for (int i = 0; i < n_fifos; ++i) {
    struct epoll_event ev = {.events = EPOLLIN};
    if (epoll_ctl(epoll, fds[i], EPOLL_CTL_ADD, &ev) == -1) {
      err(EXIT_FAILURE, "epoll_ctl");
    }
  }

  while (true) {
    struct epoll_event ev;
    switch (epoll_wait(epoll, &ev, /*maxevents=*/1, -1)) {
      case -1:
        err(EXIT_FAILURE, "epoll_wait");
      case 0:
        goto out;
    }

    char buffer[4096];
    ssize_t bytes = read_all(ev.data.fd, buffer, sizeof(buffer));
    write_all(STDOUT_FILENO, buffer, bytes);
  }

out:
  close(epoll);
  for (int i = 0; i < n_fifos; ++i) {
    close(fds[i]);
  }

  return EXIT_SUCCESS;
}
