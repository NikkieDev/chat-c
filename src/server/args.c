#include "headers/args.h"
#include "headers/network.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int arg_parse(int argc, char **argv, __uint32_t *port)
{
	char *non_nums;

	for (int i = 0; i < argc; i++)
	{
		// fprintf(stdout, "checking '%s'\n", argv[i]);
		if (strncmp(argv[i], "-p", 2) == 0)
		{
			if (argc <= 2)
					return -2;

			char start[6];
			char *portStr = argv[++i];
			--i;

			start[0] = '\0';

			strncpy(start, portStr, sizeof(start)-1);
			*port = strtol(start, &non_nums, 10); // non_nums points to first character in the string that couldn't be converted *1
			
			if (port_parse(*port) <= 0)
				return -1;
		} else if (strtol(argv[i], &non_nums, 10) != 0 && *port == 0)
		{
			*port = strtol(argv[i], &non_nums, 10);
			if (port_parse(*port) <= 0)
				return -1;
		}
	}
  return 1;
}

// *1 -> If "431Fourteentwe3lve" was passed, a char * (a string in High level) will be made with "Fourteentwelve" and integer 4313 will be parsed to the first argument (start)