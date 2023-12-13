#include <pthread.h>

#ifndef CORE_H
#define CORE_H

void exitc(signed int ecode, char *m);
void write_dump(char *m);

typedef struct client {
  int socket_fd;
  int num;
  char *buffer[2];
  char name[32];
  pthread_t thid;
} client;

#endif // CORE_H
