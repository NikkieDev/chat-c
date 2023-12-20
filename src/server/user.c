#include "headers/user.h"
#include "headers/core.h"
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
  else if (strncmp(type, "close", sizeof(type)) == 0)
    close_socket(listenPtr->user);

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

void read_chat(struct listener *listenPtr)
{
  cthreadwlistener(&listen_user, listenPtr, 1);
  cthreadwlistener(&parse_input, listenPtr, 1);

  printf("Socket descriptor: %d", listenPtr->user->socket_fd);
  if (listenPtr->user->socket_fd == -1) {
    return;
  } else {
    printf("[%s]: %s\n", listenPtr->user->name, listenPtr->recent_msg);

    char buffer[2][128*sizeof(char)];
    strncpy(buffer[0], listenPtr->user->name, 32);
    strncpy(buffer[1], listenPtr->recent_msg, 128);

    send(listenPtr->user->socket_fd, buffer, sizeof(buffer), 0);
    return;
  }
}
