#include "headers/user.h"
#include <stdio.h>
#include <string.h>

void parse_input(struct listener *listenPtr) // relocate into user.c
{
  struct listener listen = *listenPtr;
  const char *type = listen.dest[0][0];
  const char *data = listen.dest[0][1];

  if (strncmp(type, "name", sizeof(type)) == 0)
  {
    strncpy(listenPtr->user->name, data, sizeof(listenPtr->user->name));
  }

  pthread_exit(listenPtr->l_thread);
  return;
}


void listen_user(struct listener *listen)
{
  recv(listen->user->socket_fd, listen->dest, sizeof(listen->dest), 0);

  fflush(stdin);
  fflush(stdout);
 // return the listen->dest into something. Copy it don't return;
  pthread_exit(listen->l_thread);
  return;
}
