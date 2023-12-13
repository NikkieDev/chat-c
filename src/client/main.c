#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void write_server(int sock_fd)
{
  char buffer[32];

  scanf("%16s", buffer);
	int was_send = send(sock_fd, buffer, strlen(buffer), 0);
  printf("%s has been send: %d\n", buffer, was_send);

  return;
}

int try_connect(int ports[5], int persistent)
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

  persistent == 0 ? printf("Couldn't connect to server.\n"):NULL;
  return -1;
}

int try_persistent(int ports[5])
{
  int s = try_connect(ports, 1);

  while (s <= 0)
  {
    printf("Trying to connect..\n");
    fflush(stdout);
    s = try_connect(ports, 1);
    
    sleep(1);
  }

  return s;
}

int main(int argc, char **argv)
{
  int ports[5] = {3000, 3001, 3002, 3003, 30009};

  int s = try_connect(ports, 0);
  s = s == -1 ? try_persistent(ports):s;

  printf("Connected!\n");
  set_name(s);

  close(s);
}
