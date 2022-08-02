
#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#include <sys/types.h>
#include <pthread.h>


#define BUF_LEN 50

#define MAX_ROOMS 200


typedef struct client{
    u_int8_t* ip;
    int ipLen;
    int roomNumber;
    int socketDescriptor;
    char* Name;
} client;



typedef struct list{
    int capacity;
    int length;
    client* clients;

} list;

void listInit(list* ls);
void listAdd(list* ls ,client cl);
void listRemove(list* ls, client* cl);





typedef void*(*roomRoutine)(void* args);

typedef struct chat_room{
    int room_num;
    pthread_t thread;
    char isActive;
    list clientList;
    int clientsNum;
    pthread_mutex_t roomMtx;
    void (*readBuffer)(client,char*);



} chat_room;

int chatroomInit(chat_room* room, client first, roomRoutine routine);
void chatroomAdd(chat_room*room, client newClient);

void initRooms(chat_room* rooms);

#endif