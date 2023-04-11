#ifndef _ROUTINES_H_
#define _ROUTINES_H_
#include "utils.hpp"
#include "client.hpp"
extern pthread_t listener;

extern pthread_t workers[WORKERS_COUNT];
extern int socketFD;
extern sockaddr_in addr;
extern pthread_attr_t attr;

extern size_t vectorSz;
void* workRoutine(void*);
void* listenRoutine(void*);
void* manageRoutine(void*);

void acceptClient(int socket);

#endif