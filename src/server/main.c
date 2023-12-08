#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *arg_parse(int argc, char **argv, int *port)
{
	for (int i = 0; i < argc; i++)
	{
		if (strncmp(argv[i], "-p", 2) == 0)
		{
			char start[5] = argv[i+1]; // invalid init
			char *endPtr;
			*port = (int)strtol(start, *endPtr, 10);
		}
	}
}

int main(int argc, char **argv) // argv is array of arrays of chars meaning string[] in high level
{
	int port;
	void *args_parsed = arg_parse(argc, argv, &port);
	printf("%d", port);
}
