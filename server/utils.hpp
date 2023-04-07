#ifndef _UTILS_H_
#define _UTILS_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <openssl/rsa.h>

int setupServer(sockaddr_in& addr);

#endif