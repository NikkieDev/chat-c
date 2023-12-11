#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(int argc, char **argv)
{
  struct sockaddr_in addr = {.sin_family = AF_INET, .sin_port = htons(3001)};

  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
  int s = socket(AF_INET, SOCK_STREAM, 0);
  int socket_fd = connect(s, &addr, sizeof(addr));
  char buffer[256] = {0};

  strncpy(buffer, "Hello, World!\0", 64);
  puts("Sending Hello, World! To server\n");
  send(s, buffer, sizeof(buffer), 0);
  puts("sending exit!");
  strncpy(buffer, "quit\0", sizeof("quit\0"));
  send(s, buffer, sizeof(buffer), 0);

  close(s);
}