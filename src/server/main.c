#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include "headers/core.h"
#include "headers/args.h"
#include "headers/network.h"

#define MAX_USERS 30

int main(int argc, char **argv) // argv is array of arrays of chars meaning string[] in high level
{
	__uint32_t port;
	int arg_desc = arg_parse(argc, argv, &port);

	if (arg_desc <= 0)
		exitc(arg_desc, "INVALID_ARGUMENTS");
	
	int socket_fd = try_connect(port);
	int listening = listen(socket_fd, MAX_USERS);
	int users = 0;

	while (listening == 0)
	{
		pthread_t thid;
		client user = {
			.num = users+1,
			.socket_fd = socket_fd,
			.client_fd = accept(socket_fd, 0, 0)
		};

		pthread_create(&thid, NULL, accept_user, &user);
		pthread_join(thid, NULL);
		users++;
		fprintf(stdout, "Users: %d\n", users);
	}
}
