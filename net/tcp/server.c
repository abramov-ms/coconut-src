#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/un.h>

int listen_tcp(struct in_addr ip, in_port_t port) {
  int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (fd == -1) {
    err(EXIT_FAILURE, "socket");
  }

  struct sockaddr_in addr = {
      .sin_family = AF_INET,
      .sin_addr = ip,
      .sin_port = htons(port),
  };

  if (bind(fd, (const struct sockaddr*)&addr, sizeof(addr)) == -1) {
    err(EXIT_FAILURE, "bind");
  }

  if (listen(fd, SOMAXCONN) == -1) {
    err(EXIT_FAILURE, "listen");
  }

  return fd;
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

  int server_fd = listen_tcp(ip, port);

  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  for (;;) {
    int client_fd =
        accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_fd == -1) {
      err(EXIT_FAILURE, "accept");
    }

    printf("client connected ip=%s port=%d\n", inet_ntoa(client_addr.sin_addr),
           client_addr.sin_port);

    char msg[] = "hello\n";
    if (write(client_fd, msg, sizeof(msg)) == -1) {
      err(EXIT_FAILURE, "write");
    }

    for (;;) {
      char buffer[128];
      ssize_t bytes = read(client_fd, buffer, sizeof(buffer));
      if (bytes == -1) {
        err(EXIT_FAILURE, "read");
      } else if (bytes == 0) {
        break;
      }
    }

    shutdown(client_fd, SHUT_RDWR);
    close(client_fd);
  }
}
