#include "headers/user.h"
#include <stdio.h>
#include <string.h>

void parse_input(struct listener *listenPtr) // relocate into user.c
{
  struct listener listen = *listenPtr;
  const char *type = listen.dest[0];
  const char *data = listen.dest[1];

  if (strncmp(type, "name", sizeof(type)) == 0)
    strncpy(listenPtr->user->name, data, sizeof(listenPtr->user->name));
  else if (strncmp(type, "msg", sizeof(type)) == 0)
    strncpy(listenPtr->recent_msg, data, sizeof(listenPtr->recent_msg));

  pthread_exit(listenPtr->l_thread);
  return;
}

void listen_user(struct listener *listen)
{
  recv(listen->user->socket_fd, listen->dest, sizeof(listen->dest), 0);

  fflush(stdin);
  fflush(stdout);
  pthread_exit(listen->l_thread);
  return;
}
