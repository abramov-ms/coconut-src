#include <err.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

struct sockaddr_in make_addr(const char* ip_str, const char* port_str) {
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
  return addr;
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

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage: %s HOST PORT\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char* ip_str = argv[1];
  const char* port_str = argv[2];
  struct sockaddr_in server_addr = make_addr(ip_str, port_str);
  socklen_t addr_len = sizeof(server_addr);

  int sock;
  if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
    err(EXIT_FAILURE, "socket");
  }

  char buffer[4096];
  ssize_t read_bytes;
  while ((read_bytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
    ssize_t send_bytes = sendto(sock, buffer, read_bytes, /*flags=*/0,
                                (struct sockaddr*)&server_addr, addr_len);
    assert(send_bytes == read_bytes);
    ssize_t recv_bytes =
        recvfrom(sock, buffer, sizeof(buffer), /*flags=*/0, NULL, NULL);
    assert(recv_bytes == send_bytes);
    write_all(STDOUT_FILENO, buffer, recv_bytes);
  }
  if (read_bytes == -1) {
    err(EXIT_FAILURE, "read");
  }

  close(sock);
  return EXIT_SUCCESS;
}
