#include <unistd.h>

static char my_message[] = "My puts() was called\n";

int puts(const char* message) {
  write(STDOUT_FILENO, my_message, sizeof(my_message));
  return 0;
}
