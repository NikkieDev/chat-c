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

	while (listening == 0)
	{
		fprintf(stdout, "LISTENING\n");
		sleep(1);
		accept_user(socket_fd);
	}
		// pthread_t thid;
		// pthread_create(thid, NULL, accept_user, NULL);
		// pthread_join(thid, NULL);
}
