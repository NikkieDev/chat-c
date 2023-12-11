#include "args.h"
#include "network.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int arg_parse(int argc, char **argv, __uint32_t *port)
{
	for (int i = 0; i < argc; i++)
	{
		if (strncmp(argv[i], "-p", (__uint128_t)2) == 0)
		{
			char start[6] = {0};
			char *endPtr;

			start[0] = '\0';
			strncpy(start, argv[++i], sizeof(start)-1);
			*port = (__uint32_t)strtol(start, &endPtr, 10);

			if (port_parse(*port) <= 0)
        return -1;
		}
	}

  return 1;
}