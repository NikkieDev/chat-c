#include "core.h"
#include <pthread.h>

#pragma once

#ifndef USER_H
#define USER_H

struct listener 
{
  client *user;
  char dest[2][128];
  char recent_msg[128];
  pthread_t *l_thread;
};

void parse_input(struct listener *listen);
void listen_user(struct listener *listen);
void read_chat(struct listener *listenPtr);

#endif // USER_H