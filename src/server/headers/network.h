#include <stdio.h>
#include "core.h"

#ifndef NETWORK_H
#define NETWORK_H

int port_parse(int port);
int try_connect(int port);
void accept_user(client *u);

#endif // NETWORK_H