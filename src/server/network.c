#include "headers/network.h"
#include "headers/core.h"
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

signed int port_parse(int port)
{
  if (port <= 1023)
    return -1; // Special port
  else if (port > 65353)
    return -2; // Port too large
  else return 1;
}

signed int start_server(int port)
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

void accept_user(client *user)
{
  printf("accepted: %d\n", user->num);

  // while (user->socket_fd > 0)
  // {
  //   recv(user->socket_fd, user->buffer, sizeof(user->buffer), 0);
  //   if (strncmp(user->buffer, "quit", 5) == 0)
  //   {
  //     printf("received quit from user, disconnecting user.");
  //     close(user->socket_fd);
  //     pthread_exit(NULL);
  //   }
  // }

  pthread_exit(NULL);
}