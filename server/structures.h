
#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#include <sys/types.h>
#include <pthread.h>


#define BUF_LEN 71

#define MAX_ROOMS 2
//Will be max 2 rooms(threads) for the debugging and test sessions
//and so the VB will not explode


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

typedef struct clientBuffersNode{

    char clBuffer[BUF_LEN];
    int socketDescriptor;
    int bufSz;
    struct clientBuffersNode* next;

} buffersNode;

void enqueBuffer(buffersNode** head, client* descriptor);
void dequeBuffer(buffersNode** head, list* clList);

typedef void*(*roomRoutine)(void* args);

typedef struct chat_room{
    int room_num;
    pthread_t thread;
    char isActive;
    list clientList;
    int clientsNum;
    pthread_mutex_t roomMtx;
    pthread_cond_t roomCond_v;
    void (*readBuffer)(client,char*);



} chat_room;

int chatroomInit(chat_room* room, roomRoutine routine);
void chatroomAdd(chat_room*room, client newClient);

void initRooms(chat_room* rooms, roomRoutine routine);

#endif