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
#include <sys/epoll.h>

void log_info(const char* what) {
  time_t now = time(NULL);
  char time_str[128];
  strftime(time_str, sizeof(time_str), "%H:%M:%S", localtime(&now));
  fprintf(stderr, "%s INFO %s\n", time_str, what);
}

void log_error(const char* where, const char* what) {
  time_t now = time(NULL);
  char time_str[128];
  strftime(time_str, sizeof(time_str), "%H:%M:%S", localtime(&now));
  fprintf(stderr, "%s ERROR %s: %s\n", time_str, where, what);
}

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
    goto err_sock;
  }

  if (listen(sock, SOMAXCONN) == -1) {
    goto err_sock;
  }

  return sock;

err_sock:
  close(sock);
  return -1;
}

typedef struct client_ctx {
  char buffer[4096];
  size_t size;
} client_ctx_t;

void echo_accept(int epoll, int sock, client_ctx_t** clients) {
  int client;
  if ((client = accept(sock, /*addr=*/NULL, /*addr_len=*/NULL)) == -1) {
    log_error("accept", strerror(errno));
    return;
  }

  struct epoll_event client_event = {.events = EPOLLIN | EPOLLRDHUP,
                                     .data.fd = client};
  if (epoll_ctl(epoll, EPOLL_CTL_ADD, client, &client_event) == -1) {
    log_error("epoll_ctl: add client", strerror(errno));
    goto err_client;
  }

  *clients = realloc(*clients, (client + 1) * sizeof(client_ctx_t));
  (*clients)[client].size = 0;
  log_info("Connected new client");
  return;

err_client:
  shutdown(client, SHUT_RDWR);
  close(client);
}

void echo_serve(int epoll, int client, client_ctx_t* ctx,
                enum EPOLL_EVENTS events) {
  if (events & EPOLLOUT) {
    log_info("Got EPOLLOUT event");

    ssize_t bytes;
    if ((bytes = send(client, ctx->buffer, ctx->size, /*flags=*/0)) == -1) {
      log_error("send", strerror(errno));
      goto err_client;
    }
    memmove(ctx->buffer, ctx->buffer + bytes, ctx->size - bytes);
    ctx->size -= bytes;

    if (ctx->size == 0) {
      struct epoll_event event = {.events = EPOLLIN | EPOLLRDHUP,
                                  .data.fd = client};
      if (epoll_ctl(epoll, EPOLL_CTL_MOD, client, &event) == -1) {
        log_error("epoll_ctl: mod client", strerror(errno));
        goto err_client;
      }
      log_info("Discarded EPOLLOUT interest");
    }
  }

  if (events & EPOLLIN) {
    log_info("Got EPOLLIN event");

    ssize_t bytes;
    if ((bytes = recv(client, ctx->buffer + ctx->size,
                      sizeof(ctx->buffer) - ctx->size,
                      /*flags=*/0)) == -1) {
      log_error("recv", strerror(errno));
      goto err_client;
    }
    ctx->size += bytes;

    struct epoll_event event = {.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP,
                                .data.fd = client};
    if (epoll_ctl(epoll, EPOLL_CTL_MOD, client, &event) == -1) {
      log_error("epoll_ctl: mod client", strerror(errno));
      goto err_client;
    }
    log_info("Claimed EPOLLOUT interest");
  }

  if (events & EPOLLRDHUP) {
    log_info("Got EPOLLRDHUP event");
    shutdown(client, SHUT_RDWR);
    close(client);
  }

  return;

err_client:
  shutdown(client, SHUT_RDWR);
  close(client);
}

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage: %s HOST PORT\n", argv[0]);
    return EXIT_FAILURE;
  }

  int epoll;
  if ((epoll = epoll_create1(/*flags=*/0)) == -1) {
    log_error("epoll_create1", strerror(errno));
    goto err_epoll;
  }

  const char* ip_str = argv[1];
  const char* port_str = argv[2];
  int sock;
  if ((sock = init_tcp(ip_str, port_str)) == -1) {
    log_error("init_tcp", strerror(errno));
    goto err_epoll;
  }
  log_info("Launched TCP server");

  struct epoll_event sock_event = {.events = EPOLLIN, .data.fd = sock};
  if (epoll_ctl(epoll, EPOLL_CTL_ADD, sock, &sock_event) == -1) {
    log_error("epoll_ctl: sock", strerror(errno));
    goto err_sock;
  }

  client_ctx_t* clients = NULL;
  ssize_t n_fds;
  struct epoll_event events[256];
  while ((n_fds = epoll_wait(epoll, events,
                             sizeof(events) / sizeof(struct epoll_event),
                             /*timeout=*/-1)) > 0) {
    for (size_t i = 0; i < (size_t)n_fds; ++i) {
      if (events[i].data.fd == sock) {
        echo_accept(epoll, sock, &clients);
      } else {
        int client = events[i].data.fd;
        client_ctx_t* ctx = &clients[client];
        enum EPOLL_EVENTS event_mask = events[i].events;
        echo_serve(epoll, client, ctx, event_mask);
      }
    }
  }

  free(clients);
err_sock:
  close(sock);
err_epoll:
  close(epoll);
  return EXIT_FAILURE;
}
