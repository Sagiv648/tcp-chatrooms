#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include <pthread.h>
#include "structures.h"


struct sockaddr_in serverAddr;
int serverSocketDesc = -1;


void* routine(void*args){

    
    chat_room* room = (chat_room*)args;
    buffersNode* head = NULL;
    
    while(1){
        //Potentially having a linked list of user buffers will be better
        //The linked list will be initialized at the beginning of every iteration
        if(room->clientsNum == 0){
            pthread_mutex_lock(&(room->roomMtx));
            while(room->clientsNum < 1){
                pthread_cond_wait(&(room->roomCond_v), &(room->roomMtx));
                printf("room %d is now awake\n.", room->room_num);
                
            }
            pthread_mutex_unlock(&(room->roomMtx));
        }
        recieve(room, &head);
        //broadcast(room, &head);
        //recieveBuffers
        //broadcastBuffers
        
        for(;head; head = head->next){
            printf("%s ", head->clBuffer);
        }
        printf("\n-----------\n");
        
        

    }
    
}


chat_room rooms[MAX_ROOMS];

int main(int argc, char** argv){
    
    initRooms(rooms, &routine);

    serverSocketDesc = socket(AF_INET, SOCK_STREAM,0);
    if(serverSocketDesc == -1){
        perror("Failed to create a socket.\n");
        exit(1);
    }

    setServerAddr(&serverAddr);
    
    if(bind(serverSocketDesc,(struct sockaddr*)&serverAddr, sizeof(serverAddr)) != 0 ||
        listen(serverSocketDesc, 100) != 0){
            perror("error occured with server\n");
            exit(1);
        }
    printf("Server is listening.\n");
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen;
    memset(&clientAddr, 0, sizeof(clientAddr));
    client cl;

    while(1){

        cl.socketDescriptor = accept(serverSocketDesc,(struct sockaddr*)&clientAddr,&clientAddrLen);
        char buf[BUF_LEN];
        int len = read(cl.socketDescriptor, buf, BUF_LEN-1);
        if(len < sizeof(buf)){
            buf[len] = 0;
        }
        
        char* sep = strdup(strtok(buf,":"));
        cl.Name = sep;
        sep = strtok(NULL, ":");
        cl.roomNumber = atoi(sep);

        cl.ip = getipaddr(clientAddr.sin_addr.s_addr, &cl.ipLen);
        printf("connected details:\n");
        printf("Name: %s, room number: %d, socket descriptor: %d\n",cl.Name,cl.roomNumber,cl.socketDescriptor);

        pthread_mutex_lock(&(rooms[cl.roomNumber-1].roomMtx));
        if(rooms[cl.roomNumber-1].clientsNum == 0){
            printf("signaling from main\n");
            pthread_cond_signal(&(rooms[cl.roomNumber-1].roomCond_v));
        }
        chatroomAdd(&(rooms[cl.roomNumber-1]),cl);
        
        pthread_mutex_unlock(&(rooms[cl.roomNumber-1].roomMtx));
        
        
        memset(buf,0,BUF_LEN);
        
        
        

    }
        
    
    


}
