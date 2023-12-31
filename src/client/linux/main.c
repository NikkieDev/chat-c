#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "headers/network.h"
#include "headers/msg.h"

int main(void) // make windows client as well
{
  int ports[5] = {3000, 3001, 3002, 3003, 30009};
  char buffer[2][128*sizeof(char)];

  int s = try_connect(ports, 0);
  s = s == -1 ? try_persistent(ports):s;

  set_name(s);
  listen_messages(s);

  recv(s, buffer, sizeof(buffer), 0);
  printf("[%s]: %s\n", buffer[0], buffer[1]);

  close(s);
}
