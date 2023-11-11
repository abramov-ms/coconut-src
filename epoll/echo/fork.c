#include <err.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int init_tcp(const char* ip_str, const char* port_str) {
  struct in_addr ip;
  if (!inet_aton(ip_str, &ip)) {
    errno = EINVAL;
    return -1;
  }

  assert(port_str[0] != '\0');
  char* end;
  in_port_t port = strtoul(port_str, &end, /*base=*/10);
  if (errno != 0 || *end != '\0') {
    return -1;
  }

  int sock;
  if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
    return -1;
  }

  struct sockaddr_in addr = {
      .sin_family = AF_INET, .sin_addr = ip, .sin_port = htons(port)};
  socklen_t addr_len = sizeof(addr);
  if (bind(sock, (struct sockaddr*)&addr, addr_len) == -1) {
    goto err;
  }

  if (listen(sock, SOMAXCONN) == -1) {
    goto err;
  }

  return sock;

err:
  close(sock);
  return -1;
}

void log_error(int sock) {
  fprintf(stderr, "#%d: %s\n", sock, strerror(errno));
}

ssize_t send_all(int sock, const char buffer[], size_t count) {
  size_t done = 0;
  while (done < count) {
    ssize_t bytes;
    if ((bytes = send(sock, buffer + done, count - done, /*flags=*/0)) == -1) {
      return -1;
    }

    done += bytes;
  }

  return done;
}

void* echo(void* arg) {
  int sock = (int)(int64_t)arg;

  char buffer[4096];
  ssize_t bytes;
  while ((bytes = recv(sock, buffer, sizeof(buffer), /*flags=*/0)) > 0) {
    if (send_all(sock, buffer, bytes) == -1) {
      log_error(sock);
      goto out;
    }
  }
  if (bytes == -1) {
    log_error(sock);
    goto out;
  }

out:
  shutdown(sock, SHUT_RDWR);
  close(sock);
  return NULL;
}

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage: %s HOST PORT\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char* ip_str = argv[1];
  const char* port_str = argv[2];
  int sock;
  if ((sock = init_tcp(ip_str, port_str)) == -1) {
    err(EXIT_FAILURE, "init_tcp");
  }

  while (true) {
    int client;
    if ((client = accept(sock, /*addr=*/NULL, /*addr_len=*/NULL)) == -1) {
      goto out;
    }

    pthread_t thread;
    pthread_create(&thread, /*attr=*/NULL, &echo, (void*)(int64_t)client);
    pthread_detach(thread);
  }

out:
  close(sock);
  return EXIT_SUCCESS;
}
