#include <stdio.h>
#include "headers/network.h"

void set_name(int sock_fd) // call before connect + user.h
{
  char name[17];

  printf("Name: ");
  fgets(name, sizeof(name-1), stdin);
  write_server(sock_fd, "name", name);

  return;
}

void send_msg(int sock_fd, char *msg)
{
  if (strlen(msg) <= 0)
  {
    printf("BAD_MSG\n");
    return;
  } else {
    write_server(sock_fd, "msg", msg);
  }
}

void send_close(int sock_fd)
{
    const char *msg = "GRCFL";
    printf("Disconnecting..\n");

    write_server(sock_fd, "close", msg);
    close(sock_fd);

    printf("Connection closed\n");
    return;
}

void listen_messages(int sock_fd)
{
  size_t bufsize = 128;
  char msg[bufsize];

  fgets(msg, bufsize, stdin);
  msg[sizeof(msg)] = "\n";
  printf("Sending: %s\n", msg);

  if (strncmp(msg, "close", 5) == 0) {
    send_close(sock_fd);
  } else {
    send_msg(sock_fd, msg);
  }
}
