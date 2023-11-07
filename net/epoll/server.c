#include <err.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <unistd.h>

int init_tcp(const char* ip_str, const char* port_str) {
  int server_fd;
  if ((server_fd = socket(AF_INET, SOCK_STREAM, /*protocol=*/0)) == -1) {
    err(EXIT_FAILURE, "socket");
  }

  struct in_addr ip;
  if (inet_aton(ip_str, &ip) == 0) {
    fprintf(stderr, "bad ip address\n");
    exit(EXIT_FAILURE);
  }
  char* end_ptr;
  in_port_t port = strtol(port_str, &end_ptr, /*base=*/10);
  if (*end_ptr != '\0') {
    fprintf(stderr, "bad tcp port");
    exit(EXIT_FAILURE);
  }
  struct sockaddr_in server_addr = {
      .sin_family = AF_INET, .sin_addr = ip, .sin_port = htons(port)};
  if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) ==
      -1) {
    err(EXIT_FAILURE, "bind");
  }

  if (listen(server_fd, SOMAXCONN) == -1) {
    err(EXIT_FAILURE, "listen");
  }

  return server_fd;
}

int accept_client(int server_fd) {
  struct sockaddr_in client_addr = {};
  socklen_t len = sizeof(client_addr);
  int client_fd;
  if ((client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len)) ==
      -1) {
    err(EXIT_FAILURE, "accept");
  }

  return client_fd;
}

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage: %s ip port\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char* ip_str = argv[1];
  const char* port_str = argv[2];
  int server_fd = init_tcp(ip_str, port_str);

  int ep_fd;
  if ((ep_fd = epoll_create1(/*flags=*/0)) == -1) {
    err(EXIT_FAILURE, "epoll_create1");
  }

  struct epoll_event ev = {.events = EPOLLIN, .data.fd = server_fd};
  if (epoll_ctl(ep_fd, EPOLL_CTL_ADD, server_fd, &ev) == -1) {
    err(EXIT_FAILURE, "epoll_ctl");
  }

  while (true) {
    if (epoll_wait(ep_fd, &ev, /*maxevents=*/1, /*timeout=*/-1) == -1) {
      err(EXIT_FAILURE, "epoll_wait");
    }

    if (ev.data.fd == server_fd) {
      int client_fd = accept_client(server_fd);
      ev.data.fd = client_fd;
      ev.events = EPOLLIN;
      if (epoll_ctl(ep_fd, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
        err(EXIT_FAILURE, "epoll_ctl");
      }
      continue;
    }

    int client_fd = ev.data.fd;
    char buffer[4096];
    ssize_t bytes = read(client_fd, buffer, sizeof(buffer));
    assert(bytes >= 0);
    if (bytes > 0) {
      buffer[bytes] = '\0';
      printf("%d: %s\n", client_fd, buffer);
      continue;
    }

    printf("%d: <disconnected>\n\n", client_fd);
    if (epoll_ctl(ep_fd, EPOLL_CTL_DEL, client_fd, /*event=*/NULL) == -1) {
      err(EXIT_FAILURE, "epoll_ctl");
    }
    shutdown(client_fd, SHUT_RDWR);
    close(client_fd);
  }

  close(server_fd);
  return EXIT_SUCCESS;
}
