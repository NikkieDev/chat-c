#include <stdio.h>
#include "core.h"
#include "datatypes.h"

#ifndef NETWORK_H
#define NETWORK_H

int port_parse(int port);
int start_server(int port);
void accept_user(client *u);
void close_socket(struct listener *lptr);

#endif // NETWORK_H