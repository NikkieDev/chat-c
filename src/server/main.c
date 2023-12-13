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
	__uint32_t port = 0;
	int arg_desc = arg_parse(argc, argv, &port);

	if (arg_desc <= 0)
		exitc(arg_desc, "INVALID_ARGUMENTS");
	
	int sock_fd = start_server(port);
	
	int users = 0;
	
	while (1)
	{
		listen(sock_fd, MAX_USERS);
		int client_fd = accept(sock_fd, 0, 0);

		++users;
		pthread_t thid;
		client user = {
			.num = users,
			.socket_fd = client_fd,
			.thid = thid
		};

		// accept_user(&user);
		pthread_create(&thid, NULL, accept_user, &user);
		pthread_join(&thid, NULL);
	}
}