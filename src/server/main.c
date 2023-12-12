#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(WIN32)
#include <winsock2.h>
#endif
#ifdef __unix__
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#endif
#include "headers/core.h"
#include "headers/args.h"
#include "headers/network.h"

#define MAX_USERS 30

int main(int argc, char **argv) // argv is array of arrays of chars meaning string[] in high level
{
	unsigned int port;
	int arg_desc = arg_parse(argc, argv, &port);

	if (arg_desc <= 0)
		exitc(arg_desc, "INVALID_ARGUMENTS");
	
	int socket_fd = start_server(port);
	
	int users = 0;
	listening:
	listen(socket_fd, MAX_USERS);
	accept(socket_fd, 0, 0);

	++users;
	client user = {
		.num = users,
		.socket_fd = socket_fd,
	};

	#if defined(WIN32)
		accept_user(&user);
	#else
		pthread_t thid;
		pthread_create(&thid, NULL, accept_user, &user);
		pthread_join(thid, NULL);
	#endif
	goto listening;
}