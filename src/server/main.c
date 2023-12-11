#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "core.h"

int main(int argc, char **argv) // argv is array of arrays of chars meaning string[] in high level
{
	__uint32_t port;
	int arg_desc = arg_parse(argc, argv, &port);

	if (arg_desc <= 0)
		exitc(arg_desc, "INVALID_ARGUMENTS");
	printf("PORT: %d\n", port);
}
