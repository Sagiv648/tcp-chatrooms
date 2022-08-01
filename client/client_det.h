typedef struct client{
    int socketFD;
    int connected;
    int room;
    char userName[20];
    char incomingBuffer[50];


} client;

void initClient(client* cl, int s_fd, char* userName, int room);