
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utility.h"
#include "structures.h"

void initRooms(chat_room* rooms, roomRoutine routine){

    int i;
    for(i = 0; i < MAX_ROOMS; i++){
        rooms[i].isActive = 0;
        rooms[i].clientsNum = 0;
        listInit(&rooms[i].clientList);
        rooms[i].room_num = i+1;
        rooms[i].readBuffer = &readBuffer;
        pthread_mutex_init(&rooms[i].roomMtx, NULL);
        pthread_cond_init(&rooms[i].roomCond_v, NULL);
        chatroomInit(&rooms[i], routine);
    }
    
    
}


int chatroomInit(chat_room* room, roomRoutine routine){

    
    //pthread_mutex_lock (&room->roomMtx);
    room->isActive = 1;
    //room->clientsNum = 0;
    //listAdd(&room->clientList,first);
    //pthread_mutex_unlock (&room->roomMtx);
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if(pthread_create(&room->thread, &attr, routine,(void*)room) != 0){

        
        perror("error occured with thread");
        return 0;
    }
    //printf("chatroom init here\n");
    pthread_attr_destroy(&attr);
    return 1;

}
void chatroomAdd(chat_room*room, client newClient){

    
    room->clientsNum++;
    listAdd(&room->clientList,newClient);
    
}

void listInit(list* ls){
    ls->capacity = 5;
    ls->length = 0;
    ls->clients = malloc(ls->capacity*sizeof(client));
    if(!ls->clients){
        perror("not enough memory\n");
        exit(1);
    }
}

void listAdd(list* ls ,client cl){
    if(ls->capacity - ls->length == 1){
        ls->capacity += 5;
        client* pClient = realloc(ls->clients, ls->capacity*sizeof(client));
        if(!pClient){
            perror("Not enough memory\n");
            exit(1);
        }
        ls->clients = pClient;
        pClient = NULL;
        

    }
    ls->clients[ls->length] = cl;
    ls->length++;

}
void listRemove(list* ls, client* cl){
    int i = 0;
    for(i = 0; i < ls->length; i++){
        if((ls->clients+i) == cl){
            break;
        }
    }

    for(int j = i+1; j < ls->length; j++){
        ls->clients[j-1] = ls->clients[j];
    }
    ls->length--;
    if(ls->capacity - ls->length > 5){
        ls->capacity -= 5;
        client* pClient = realloc(ls->clients, ls->capacity*sizeof(client));
        if(!pClient){
            perror("not enough memory\n");
            exit(1);
        }
        ls->clients = pClient;
        pClient = NULL;
    }

}

void enqueBuffer(buffersNode* head, int descriptor){

    int len;
    if(!head){
        head = malloc(sizeof(buffersNode));
        head->next = NULL;
        len = read(descriptor, head->clBuffer, BUF_LEN);
        head->clBuffer[len] = 0;
        head->socketDescriptor = descriptor;
        head->bufSz = len+1;
        return;
        
    }
    buffersNode* tmp = head;
    for(;tmp->next != NULL;tmp = tmp->next);
    tmp->next = malloc(sizeof(buffersNode));
    tmp->next = NULL;
    len = read(descriptor, tmp->clBuffer, BUF_LEN);
    tmp->clBuffer[len] = 0;
    tmp->socketDescriptor = descriptor;
    
}
void dequeBuffer(buffersNode* head, list* clList){
    int i;
    for(i = 0; i < clList->length; i++){
        if(clList->clients[i].socketDescriptor == head->socketDescriptor){
            continue;
        }
        write(clList->clients[i].socketDescriptor, head->clBuffer,head->bufSz);

    }
    buffersNode* tmp = head->next;
    free(head);
    head = tmp;
}