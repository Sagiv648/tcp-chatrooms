#include "client_det.h"
#include <string.h>

void initClient(client* cl, int s_fd, char* userName, int room){

    cl->socketFD = s_fd;
    cl->connected = 1;
    cl->room = room;

    strcpy(cl->userName, userName);
    //printf("initclient -> %s and username -> %s\n", cl->userName, userName);
    memset(&cl->incomingBuffer,0, sizeof(cl->incomingBuffer));
}