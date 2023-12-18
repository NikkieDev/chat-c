#include "headers/core.h"
#include <stdlib.h>
#include <stdio.h>

void exitc(signed int exitcode, char *message)
{
	printf("[%d] %s\n", exitcode, message);
	exit(exitcode);
};