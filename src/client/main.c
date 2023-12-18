#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void write_server(int sock_fd, char *type, char *buffer) // network.h
{
  char cache[2][128];

  // printf("Allocating for [Type: %s; Data: %s]\n", type, buffer);
  fflush(stdout);

  strncpy(cache[0], type, sizeof(cache[0]));
  strncpy(cache[1], buffer, sizeof(cache[1]));

  size_t cache_len = sizeof(cache);
  char sendStr[128];

	int was_send = send(sock_fd, cache, cache_len, 0);
  return;
}

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

int try_connect(int ports[5], int persistent) // network.h
{
  for (size_t i = 0; i < 5; i++)
  {
    struct sockaddr_in addr = {.sin_family = AF_INET, .sin_port = htons(ports[i])};
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    int s = socket(AF_INET, SOCK_STREAM, 0);
    int socket_fd = connect(s, &addr, sizeof(addr));
    
    if (socket_fd < 0)
      continue;
    else
    {
      printf("Connecting to [*:%d]\n", ports[i]);
      return s;
    }
  }

  persistent == 0 ? printf("Couldn't connect to server.\n"):printf(NULL);
  return -1;
}

int try_persistent(int ports[5]) // network.h
{
  int s = try_connect(ports, 1);
  int tries = 0;

  while (s <= 0)
  {
    if (tries >= 15)
    {
      printf("A connection to the server could not be established. Try again later.\n");
      exit(-11);
    }

    printf("Trying to connect..\n");
    fflush(stdout);
    s = try_connect(ports, 1);
    
    sleep(1);
    ++tries;
  }

  return s;
}


int main(void) // make windows client as well
{
  int ports[5] = {3000, 3001, 3002, 3003, 30009};
  char buffer[2][384*4];

  int s = try_connect(ports, 0);
  s = s == -1 ? try_persistent(ports):s;

  printf("Connected!\n");
  set_name(s);

  listen_messages(s);
  recv(s, buffer, 500*4, 0);
  printf("[%s]: %s\n", buffer[0], buffer[1]);

  close(s);
}
