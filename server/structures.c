#include "structures.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void initRooms(chat_room* rooms){

    int i;
    for(i = 0; i < MAX_ROOMS; i++){
        rooms[i].isActive = 0;
        rooms[i].clientsNum = 0;
        rooms[i].client = NULL;
        rooms[i].room_num = i+1;
    }
    
}


int chatroomInit(chat_room* room, client first, roomRoutine routine){

    pthread_mutex_unlock (&room->roomMtx);
    room->isActive = 1;
    room->clientsNum = 1;
    pthread_mutex_unlock (&room->roomMtx);

    room->client = malloc(room->clientsNum*sizeof(client*));
    room->client[room->clientsNum-1] = malloc(sizeof(client));

    room->client[room->clientsNum-1]->ip = first.ip;
    room->client[room->clientsNum-1]->ipLen = first.ipLen;
    room->client[room->clientsNum-1]->Name = first.Name;
    room->client[room->clientsNum-1]->roomNumber = first.roomNumber;
    room->client[room->clientsNum-1]->socketDescriptor = first.socketDescriptor;
    pthread_mutex_init(&room->roomMtx, NULL);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if(pthread_create(&room->thread, &attr, routine,(void*)room) != 0){
        pthread_attr_destroy(&attr);
        perror("error occured with thread");
        return 0;
    }
    //printf("chatroom init here\n");
    pthread_attr_destroy(&attr);
    return 1;

}
void chatroomAdd(chat_room*room, client newClient){

    pthread_mutex_lock(&room->roomMtx);
    //printf("chatroom add here\n");
    room->client = realloc(room->client, ++room->clientsNum*sizeof(client*));
    room->client[room->clientsNum-1] = malloc(sizeof(client));

    room->client[room->clientsNum-1]->ip = newClient.ip;
    room->client[room->clientsNum-1]->ipLen = newClient.ipLen;
    room->client[room->clientsNum-1]->Name = newClient.Name;
    room->client[room->clientsNum-1]->roomNumber = newClient.roomNumber;
    room->client[room->clientsNum-1]->socketDescriptor = newClient.socketDescriptor;
    pthread_mutex_unlock(&room->roomMtx);
}