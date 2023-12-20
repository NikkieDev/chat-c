#include <pthread.h>
#include "datatypes.h"

#ifndef CORE_H
#define CORE_H

void exitc(signed int ecode, char *m);
pthread_t cthreadwlistener(void *__func, struct listener *__listenerPtr, int _join);

#endif // CORE_H
