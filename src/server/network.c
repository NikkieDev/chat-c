#include "headers/network.h"
#include "headers/core.h"
#include <stdio.h>
#include <pthread.h>
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

struct listener 
{
  client *user;
  char dest[256];
} listener;

void listen_user(struct listener *listen)
{
  recv(listen->user->socket_fd, listen->user->buffer, sizeof(listen->user->buffer), 0);
  
  if (strlen(listen->user->buffer) >= 256)
  {
    exitc(-11, "BUFFER_OVERFLOW");
  }

  listen->user->buffer[strlen(listen->user->buffer)] = '\0';
  strncpy(listen->dest, listen->user->buffer, sizeof(listen->dest));
  fflush(stdin);
  fflush(stdout);

  return 0;
}

void accept_user(client *user)
{
  pthread_t thid;

  struct listener listen = {
    .user = user
  };

  printf("New user connected\n");

  listen_user(&listen);
  printf("client-%d: %s\n", user->num, listen.dest);

  close(user->socket_fd);
  printf("User disconnected\n");
  
  pthread_exit(user->thid);
  return;
}
