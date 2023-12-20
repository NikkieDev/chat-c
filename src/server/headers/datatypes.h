#include <pthread.h>

#ifndef DATATYPES_H
#define DATATYPES_H
#pragma once

typedef struct client {
  int socket_fd;
  int num;
  char *buffer[2];
  char name[32];
  char recent_msg[128];
  pthread_t thid;
} client;

struct listener 
{
  client *user;
  char dest[2][128];
  pthread_t *l_thread;
};

#endif