#include "headers/network.h"
#include "headers/core.h"
#include <stdio.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define RED_COL "\033[0;31m";
#define DEF_COL "\033[0m";

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
  char dest[2][33];
} listener;

void listen_user(struct listener *listen)
{
  recv(listen->user->socket_fd, listen->dest, sizeof(listen->dest), 0);
  
  if (sizeof(listen->dest) >= 256)
  {
    exitc(-11, "BUFFER_OVERFLOW");
  }

  fflush(stdin);
  fflush(stdout);

  return 0;
}

void parse_input(struct listener listen) // relocate into user.c
{
  const char *type = listen.dest[0];
  const char *data = listen.dest[1];
  struct listener *listenPtr = &listen;

  if (strncmp(type, "name", sizeof(type)) == 0)
  {
    strncpy(listenPtr->user->name, data, sizeof(listenPtr->user->name));
  }

  return;
}

void accept_user(client *user)
{
  pthread_t thid;

  struct listener listen = {
    .user = user
  };

  printf("New user connected\n");

  listen_user(&listen);
  parse_input(listen);

  printf("\033[0;31mUser data:\n\t[NAME]: %s\n\033[0m", user->name);

  close(user->socket_fd);
  printf("User disconnected\n");
  
  pthread_exit(user->thid);
  return;
}
