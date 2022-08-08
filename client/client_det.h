#ifndef _CLIENT_DET_H_
#define _CLIENT_DET_H_

#define BUF_LEN 51

typedef struct client{
    int socketFD;
    int connected;
    int room;
    char userName[20];
    char incomingBuffer[50];


} client;

void initClient(client* cl, int s_fd, char* userName, int room);

#endif