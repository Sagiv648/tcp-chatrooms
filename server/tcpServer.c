#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include <pthread.h>
#include "structures.h"


struct sockaddr_in serverAddr;
int serverSocketDesc = -1;

//TODO: Debugging
//TODO: Plan the overlaying structure of the program
//TODO: a function which will handle the resources de-allocation upon termination of a chat room

void* routine(void*args){
//TODO:
//1. a function to iterate over all open sockets and retrieve the buffers sent.
//2. a function to iterate over all open sockets and broadcast the buffers to them.


    chat_room* room = (chat_room*)args;

    while(1){
        //debugging purposes
        char buf[20];
        int len = read(room->client[0]->socketDescriptor, buf, 20);
        //printf("details are: name - %s, room num - %d, descriptor - %d\n", room->client[0].Name, room->client[0].roomNumber, room->client[0].socketDescriptor);
        //if(len < sizeof(buf)) buf[len-1] = 0;
        if(len > 0){
            buf[len] = 0;
            printf("client sent -> %s\n", buf);
            
        }
            
        
    }

    pthread_mutex_lock (&room->roomMtx);
    free(room->client);
    room->isActive = 0;
    room->clientsNum = 0;
    pthread_mutex_unlock(&room->roomMtx);
    
}


chat_room rooms[MAX_ROOMS];

int main(int argc, char** argv){
    
    initRooms(rooms);

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
        if(cl.socketDescriptor){
            char buf[30];
        int len = read(cl.socketDescriptor, buf, sizeof(buf));
        if(len < sizeof(buf)){
            buf[len] = 0;
        }
        //printf("buf connectionMsg -> %s\n", buf);
        //parsing the client's initial connection msg, specify the client's name and the room number
        char* sep = strtok(buf,":");
        cl.Name = sep;
        //printf("reached here.\n");
        //printf("reached here -> %s\n", cl.Name);
        //printf("first sep -> %s\n", sep);
        sep = strtok(NULL, ":");
        //printf("second sep -> %s\n", sep);
        cl.roomNumber = atoi(sep);

        
        //printf("user name -> %s | room number -> %d\n", cl.Name, cl.roomNumber);

        
        cl.ip = getipaddr(clientAddr.sin_addr.s_addr, &cl.ipLen);
        
        if(rooms[cl.roomNumber-1].isActive == 0){
            chatroomInit(&rooms[cl.roomNumber-1], cl, &routine);
        }
        else{
            chatroomAdd(&rooms[cl.roomNumber-1],cl);
        }
        }
        
        

    }
        
    
    


}
