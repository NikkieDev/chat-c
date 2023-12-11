#include "headers/args.h"
#include "headers/network.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int arg_parse(int argc, char **argv, __uint32_t *port)
{
	if (argc <= 2)
		return -2;

	for (int i = 0; i < argc; i++)
	{
		// fprintf(stdout, "checking '%s'\n", argv[i]);
		if (strncmp(argv[i], "-p", 2) == 0)
		{
			char start[6];
			char *portStr = argv[++i];
			char *endPtr;
			--i;

			start[0] = '\0';

			strncpy(start, portStr, sizeof(start)-1);
			*port = strtol(start, &endPtr, 10); // endPtr = first character in the string that couldn't be converted *1
			
			if (port_parse(*port) <= 0)
				return -1;
		}
	}
  return 1;
}

// *1 -> If "431Fourteentwe3lve" was passed, a char * (a string in High level) will be made with "Fourteentwelve" and integer 4313 will be parsed to the first argument (start)