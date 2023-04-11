#ifndef _UTILS_H_
#define _UTILS_H_
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>

#include <openssl/rsa.h>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <memory>
#include "sys/epoll.h"
#define WORKERS_COUNT 10
#define HEADER_MAX_BYTES 150
int setupServer(sockaddr_in& addr);




#endif