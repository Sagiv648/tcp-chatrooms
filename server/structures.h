#include <sys/types.h>
#include <pthread.h>


#define MAX_ROOMS 200


typedef struct client{
    u_int8_t* ip;
    int ipLen;
    int roomNumber;
    int socketDescriptor;
    char* Name;
} client;




typedef void*(*roomRoutine)(void* args);

typedef struct chat_room{
    int room_num;
    pthread_t thread;
    char isActive;
    client** client;
    int clientsNum;
    pthread_mutex_t roomMtx;


} chat_room;

int chatroomInit(chat_room* room, client first, roomRoutine routine);
void chatroomAdd(chat_room*room, client newClient);

void initRooms(chat_room* rooms);