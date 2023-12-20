#include <pthread.h>

#ifndef CORE_H
#define CORE_H

typedef struct client {
  int socket_fd;
  int num;
  char *buffer[2];
  char name[32];
  pthread_t thid;
} client;

struct listener 
{
  client *user;
  char dest[2][128];
  char recent_msg[128];
  pthread_t *l_thread;
};


void exitc(signed int ecode, char *m);
pthread_t cthreadwlistener(void *__func, struct listener *__listenerPtr, int _join);

#endif // CORE_H
