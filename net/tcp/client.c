#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int dial_tcp(const char* ip_str, const char* port_str) {
  int server_fd;
  if ((server_fd = socket(AF_INET, SOCK_STREAM, /*protocol=*/0)) == -1) {
    err(EXIT_FAILURE, "socket");
  }

  struct in_addr ip = {};
  if (inet_aton(ip_str, &ip) == 0) {
    fprintf(stderr, "bad ip address");
    exit(EXIT_FAILURE);
  }
  char* end_ptr;
  in_port_t port = strtol(port_str, &end_ptr, /*base=*/10);
  if (*end_ptr != '\0') {
    fprintf(stderr, "bad tcp port");
    exit(EXIT_FAILURE);
  }
  struct sockaddr_in addr = {
      .sin_family = AF_INET, .sin_port = htons(port), .sin_addr = ip};
  if (connect(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    err(EXIT_FAILURE, "connect");
  }

  return server_fd;
}

void send_all(int sock, char* buffer, size_t count) {
  size_t done = 0;
  while (done < count) {
    ssize_t bytes = send(sock, buffer + done, count - done, /*flags=*/0);
    if (bytes == -1) {
      err(EXIT_FAILURE, "send");
    }
    done += bytes;
  }
}

void write_all(int fd, char* buffer, size_t count) {
  size_t done = 0;
  while (done < count) {
    ssize_t bytes = write(fd, buffer + done, count - done);
    if (bytes == -1) {
      err(EXIT_FAILURE, "write");
    }
    done += bytes;
  }
}

void* reader(void* arg) {
  int sock = (int)(int64_t)arg;
  char buffer[4096];
  ssize_t bytes;
  while ((bytes = recv(sock, buffer, sizeof(buffer), /*flags=*/0)) > 0) {
    write_all(STDOUT_FILENO, buffer, bytes);
  }
  if (bytes == -1) {
    err(EXIT_FAILURE, "recv");
  }

  shutdown(sock, SHUT_RD);
  return NULL;
}

void* writer(void* arg) {
  int sock = (int)(int64_t)arg;
  char buffer[4096];
  ssize_t bytes;
  while ((bytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
    send_all(sock, buffer, bytes);
  }
  if (bytes == -1) {
    err(EXIT_FAILURE, "read");
  }

  shutdown(sock, SHUT_WR);
  return NULL;
}

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage: %s HOST PORT\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char* ip_str = argv[1];
  const char* port_str = argv[2];
  int sock = dial_tcp(ip_str, port_str);

  pthread_t r;
  pthread_create(&r, /*attr=*/NULL, &reader, (void*)(int64_t)sock);
  pthread_t w;
  pthread_create(&w, /*attr=*/NULL, &writer, (void*)(int64_t)sock);
  pthread_join(r, /*thread_return=*/NULL);
  pthread_join(w, /*thread_return=*/NULL);

  close(sock);
  return EXIT_SUCCESS;
}
