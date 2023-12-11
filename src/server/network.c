#include "headers/network.h"
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>

signed int port_parse(int port)
{
  if (port <= 1023)
    return -1; // Special port
  else if (port > 65353)
    return -2; // Port too large
  else return 1;
}

signed int try_connect(int port)
{
  int s = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_addr = 0,
    .sin_port = htons(port)
  };

  bind(s, &addr, sizeof(addr));

  return s;
}

void accept_user(int accepted_fd)
{
  printf("accepted: %d\n", accepted_fd);
  // close(accepted_fd);

  pthread_exit(NULL);
}