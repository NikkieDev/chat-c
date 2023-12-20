#include "headers/core.h"
#include "headers/user.h"

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void exitc(signed int exitcode, char *message)
{
	printf("[%d] %s\n", exitcode, message);
	exit(exitcode);
};

pthread_t cthreadwlistener(void *__func, struct listener *__listenerPtr, int _join)
{
  pthread_t thid;
  pthread_create(__listenerPtr->l_thread, NULL, __func, __listenerPtr);
  
  if (_join)
  {
    pthread_join(*__listenerPtr->l_thread, NULL);
  }

  return thid;
}