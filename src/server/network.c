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
  if (port == 65353)
  {
    printf("No available ports. Exiting..\n");
    exit(0);
  }
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

pthread_t cthreadwlistener(void *__func, struct listener *__listenerPtr, int _join)
{
  pthread_t thid;
  pthread_create(__listenerPtr->l_thread, NULL, __func, __listenerPtr);
  
  if (_join)
  {
    pthread_join(*__listenerPtr->l_thread, NULL);
  }

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
  cthreadwlistener(&listen_user, listenPtr, 1);
  cthreadwlistener(&parse_input, listenPtr, 1);

  printf("\033[0;31mUser data:\n\t[NAME]: %s\n\033[0m", listenPtr->user->name);

  close(user->socket_fd);
  printf("%s disconnected\n", listenPtr->user->name);
  
  pthread_exit(user->thid);
  return;
}
