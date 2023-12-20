#include <pthread.h>


#ifndef USER_H
#define USER_H
void parse_input(struct listener *listen);
void listen_user(struct listener *listen);
void read_chat(struct listener *listenPtr);

#endif // USER_H