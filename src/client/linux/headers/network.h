#ifndef NETWORK_H
#define NETWORK_H

int write_server(int s, char *T, char *B);
int try_connect(int *P, int pstnt);
int try_persistent(int *P);

#endif // NETWORK_H