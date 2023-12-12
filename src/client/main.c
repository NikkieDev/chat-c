#if defined(WIN32)
#include <WinSock2.h>
#include <ws2tcpip.h>
#endif

#ifdef __unix__
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include <stdio.h>
#include <string.h>

void write_server(int sock_fd)
{
  char buffer[256];
  char input[16];

  scanf("%s", input);
	strncpy(buffer, input, sizeof(buffer));
	send(sock_fd, buffer, sizeof(buffer), 0);
  return;
}

int try_connect(int ports[5])
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
      fprintf(stdout, "Connecting to [*:%d]\n", ports[i]);
      return s;
    }
  }

  printf("Couldn't connect to server.\n");
  return -1;
}

int main(int argc, char **argv)
{
  int ports[5] = {3000, 3001, 3002, 3003, 30009};

  int s = try_connect(ports);
	
  while(1 && s >= 0)
  {
    write_server(s);
  }

  close(s);
}
