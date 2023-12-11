#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
void exitc(signed int exitcode, char *message)
{
	printf(message);
	exit(exitcode);
}

int main(int argc, char **argv) // argv is array of arrays of chars meaning string[] in high level
{
	__uint32_t port;
	
	if (arg_parse(argc, argv, &port) <= 0)
		exitc(-1, "INVALID_ARGUMENTS");
	printf("PORT: %d\n", port);
}
