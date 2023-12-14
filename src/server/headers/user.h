#include "core.h"
#include <pthread.h>

#pragma once

#ifndef USER_H
#define USER_H

struct listener 
{
  client *user;
  char dest[10][2][33];
  pthread_t *l_thread;
};

void parse_input(struct listener *listen);
void listen_user(struct listener *listen);

#endif // USER_H