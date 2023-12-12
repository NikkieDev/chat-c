#include "headers/network.h"
#include "headers/core.h"
#include <stdio.h>
#include <string.h>

#if defined(WIN32)
#include <WinSock2.h>
#include <ws2tcpip.h>
#endif

#ifdef __unix__
#include <netinet/in.h>
#include <sys/socket.h>
#endif


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
    AF_INET,
    htons(port),
    0
  };

  bind(s, &addr, sizeof(addr));

  return s;
}

void listen_user(char **dest, client *user)
{
  recv(user->socket_fd, user->buffer, sizeof(user->buffer), 0);
  
  user->buffer[strlen(user->buffer)+1] = '\0';
  strncpy(dest, user->buffer, sizeof(dest));

  return;
}

void accept_user(client *user)
{
  printf("Client %d has joined\n", user->num);

  char buffer[sizeof(user->buffer)];
  listen_user(&buffer, &user);
  printf("%s", buffer);
  
  if (strncmp(buffer, "quit", 4) == 0)
  {
    memset(buffer, 0, sizeof(buffer));
    printf("Closing user...\n");

    close(user->socket_fd);
    return;
  } else
  {
    char output_buffer[sizeof(buffer)+sizeof(user->num)+12];
    snprintf(output_buffer, sizeof(output_buffer), "[client]: %s\n", user->buffer);
    printf(output_buffer);

    listen_user(&buffer, user);
    fflush(stdout);
  }

  return;
}
