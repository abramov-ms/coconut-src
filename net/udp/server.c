#include <err.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int init_udp(const char* ip_str, const char* port_str) {
  struct in_addr ip;
  if (inet_aton(ip_str, &ip) == 0) {
    fprintf(stderr, "bad ip address\n");
    exit(EXIT_FAILURE);
  }
  char* end_ptr;
  in_port_t port = strtol(port_str, &end_ptr, /*base=*/10);
  if (*end_ptr != '\0') {
    fprintf(stderr, "bad udp port");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in addr = {
      .sin_family = AF_INET, .sin_addr = ip, .sin_port = htons(port)};

  int sock;
  if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    err(EXIT_FAILURE, "socket");
  }

  if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    err(EXIT_FAILURE, "bind");
  }

  return sock;
}

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage: %s HOST PORT\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char* ip_str = argv[1];
  const char* port_str = argv[2];
  int sock = init_udp(ip_str, port_str);

  char buffer[4096];
  struct sockaddr_in client_addr;
  socklen_t addr_len = sizeof(client_addr);
  while (true) {
    ssize_t recv_bytes = recvfrom(sock, buffer, sizeof(buffer), /*flags=*/0,
                                  (struct sockaddr*)&client_addr, &addr_len);
    assert(recv_bytes >= 0);
    ssize_t send_bytes = sendto(sock, buffer, recv_bytes, /*flags=*/0,
                                (struct sockaddr*)&client_addr, addr_len);
    assert(send_bytes == recv_bytes);
  }

  close(sock);
  return EXIT_SUCCESS;
}
