#include "core.h"

#pragma once

#ifndef USER_H
#define USER_H

struct listener 
{
  client *user;
  char dest[2][33];
};

void parse_input(struct listener listen);
void listen_user(struct listener *listen);

#endif // USER_H