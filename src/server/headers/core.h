#ifndef CORE_H
#define CORE_H

void exitc(signed int exitcode, char *message);

typedef struct client {
  int socket_fd;
  int client_fd;
  int num;
  char buffer[256]
} client;

#endif // CORE_H