#include <stdio.h>

#ifndef NETWORK_H
#define NETWORK_H

int port_parse(int port);
int try_connect(int port);
void accept_user(int s_fd);

#endif // NETWORK_H