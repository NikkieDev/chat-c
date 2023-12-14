#include "headers/network.h"
#include "headers/core.h"
#include "headers/user.h"

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

unsigned int try_bind(int *sock, struct sockaddr_in addr, int port)
{
  struct sockaddr_in *addrPtr = &addr;
  addrPtr->sin_port = htons(port);

  int tried = bind(*sock, addrPtr, sizeof(addr));

  if (tried == -1)
  {
    printf("Couldn't bind to [*:%d], binding to [*:%d]\n", port, port+1);
    ++port;sleep(1);
    try_bind(sock, addr, port);
  } else
  {
    printf("Binding to [*:%d]\n", port);
    return tried;
  }
}

signed int start_server(int port)
{
  int s = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_addr = 0
  };

  try_bind(&s, addr, port);

  return s;
}

pthread_t cthreadwlistener(void *__func, client *__user)
{
  pthread_t thid;
  struct listener __listener = {.user = __user, .l_thread = thid};
  struct listener *listenerPtr = &__listener;
  
  pthread_create(&listenerPtr->l_thread, NULL, __func, listenerPtr);
  return thid;
}

void accept_user(client *user)
{
  pthread_t thid, thid2;
  pthread_t thread_list[2];

  struct listener listen = {
    .user = user
  };

  struct listener *listenPtr = &listen;
  listenPtr->l_thread = &thid;

  // segfault
  cthreadwlistener(&listen_user, &listenPtr->user);
  cthreadwlistener(&parse_input, &listenPtr->user);

  printf("Thread value: %ld", thid);
  
  printf("\033[0;31mUser data:\n\t[NAME]: %s\n\033[0m", user->name);

  close(user->socket_fd);
  printf("%s disconnected\n", user->name);
  
  pthread_exit(user->thid);
  return;
}
