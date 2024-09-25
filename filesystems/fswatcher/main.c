#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <error.h>
#include <errno.h>

#include <limits.h>
#include <unistd.h>

#include <sys/inotify.h>

const char* event_mask_to_message(uint32_t inotify_event_mask) {
  if (inotify_event_mask & IN_CREATE) {
    return "created";
  } else if (inotify_event_mask & IN_DELETE) {
    return "deleted";
  } else if (inotify_event_mask & IN_MOVED_FROM) {
    return "moved from";
  } else if (inotify_event_mask & IN_MOVED_TO) {
    return "moved to";
  } else if (inotify_event_mask & IN_MODIFY) {
    return "modified";
  }

  assert(false && "unknown event type");
}

void log_event(FILE* file, struct inotify_event* event) {
  fprintf(file, "%s: %s\n", event->name, event_mask_to_message(event->mask));
  fflush(file);
}

int watch_path(int inotify_fd, const char* path) {
  return inotify_add_watch(inotify_fd, path,
                           IN_CREATE | IN_DELETE | IN_MOVE | IN_MODIFY);
}

void print_usage(FILE* file, const char* executable) {
  fprintf(file, "usage: %s DIRECTORY_TO_WATCH\n", executable);
}

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    print_usage(stderr, argv[0]);
    return EXIT_FAILURE;
  }

  int inotify_fd = inotify_init();
  if (inotify_fd == -1) {
    error(EXIT_FAILURE, errno, "inotify_init");
  }

  const char* dir_under_watch = argv[1];
  int watch_fd = watch_path(inotify_fd, dir_under_watch);
  if (watch_fd == -1) {
    error(EXIT_FAILURE, errno, "watch_path");
  }

  while (true) {
    char buffer[sizeof(struct inotify_event) + NAME_MAX + 1];

    int bytes = read(inotify_fd, buffer, sizeof(buffer));
    if (bytes == -1) {
      error(EXIT_FAILURE, errno, "read");
    }

    struct inotify_event* event = (struct inotify_event*)buffer;

    log_event(stdout, event);
  }
}
