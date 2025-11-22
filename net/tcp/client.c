#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <pthread.h>

#include <arpa/inet.h>
#include <sys/un.h>

int new_socket() {
  int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (fd == -1) {
    err(EXIT_FAILURE, "socket");
  }

  return fd;
}

void write_all(int fd, const char* buffer, size_t len) {
  for (; len > 0;) {
    ssize_t bytes = write(fd, buffer, len);
    if (bytes == -1) {
      err(EXIT_FAILURE, "write");
    }
    buffer += bytes;
    len -= bytes;
  }
}

void* read_response(void* arg) {
  int* server_fd = arg;

  for (;;) {
    char buffer[128];
    ssize_t bytes = read(*server_fd, buffer, sizeof(buffer));
    if (bytes == -1) {
      err(EXIT_FAILURE, "read");
    } else if (bytes == 0) {
      break;
    }

    write_all(STDOUT_FILENO, buffer, bytes);
  }

  return NULL;
}

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    printf("usage: %s <ip> <port>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char* ip_str = argv[1];
  const char* port_str = argv[2];

  struct in_addr ip;
  if (inet_aton(ip_str, &ip) == -1) {
    err(EXIT_FAILURE, "inet_aton");
  }

  in_port_t port = atoi(port_str);

  int server_fd = new_socket();

  struct sockaddr_in server_addr = {
      .sin_family = AF_INET,
      .sin_addr = ip,
      .sin_port = htons(port),
  };

  if (connect(server_fd, (const struct sockaddr*)&server_addr,
              sizeof(server_addr)) == -1) {
    err(EXIT_FAILURE, "connect");
  }

  pthread_t reader;
  pthread_create(&reader, NULL, &read_response, &server_fd);

  for (;;) {
    char buffer[128];
    ssize_t bytes = read(STDIN_FILENO, buffer, sizeof(buffer));

    if (bytes == -1) {
      err(EXIT_FAILURE, "read");
    } else if (bytes == 0) {
      break;
    }

    write_all(server_fd, buffer, bytes);
  }

  shutdown(server_fd, SHUT_RDWR);
  close(server_fd);

  pthread_join(reader, NULL);

  return 0;
}
