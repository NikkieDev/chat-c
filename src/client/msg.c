#include <stdio.h>

void set_name(int sock_fd) // call before connect + user.h
{
  char name[17];

  printf("Name: ");
  scanf("%16s *[^\n]", name); // *[^\n] Ignore everything until newline, and flush newline
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

void listen_messages(int sock_fd)
{
  char msg[128];
  size_t bufsize = 128;

  fgets(msg, bufsize, stdin);
  msg[sizeof(msg)] = NULL;
  send_msg(sock_fd, msg);

  return;
}