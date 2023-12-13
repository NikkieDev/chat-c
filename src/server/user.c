#include "headers/user.h"
#include <stdio.h>

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
