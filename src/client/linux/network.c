#include "headers/network.h"

#include <stdio.h>
#include <arpa/inet.h>

int write_server(int sock_fd, char *type, char *buffer) // network.h
{
  char cache[2][128];

  // printf("Allocating for [Type: %s; Data: %s]\n", type, buffer);
  fflush(stdout);

  strncpy(cache[0], type, sizeof(cache[0]));
  strncpy(cache[1], buffer, sizeof(cache[1]));

  size_t cache_len = sizeof(cache);
  char sendStr[128];
  
  int was_send = send(sock_fd, cache, cache_len, 0);
  return was_send;
}

int try_connect(int *ports, int persistent) // network.h
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

int try_persistent(int *ports) // network.h
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
