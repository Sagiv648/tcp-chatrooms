#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>


void setServerAddr(struct sockaddr_in* addr);

char** readFromFile(int* len);

uint8_t* getipaddr(uint32_t networkedIP, uint32_t* len);

#endif