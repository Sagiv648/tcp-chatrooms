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

//3. a function to fully read a read buffer

    chat_room* room = (chat_room*)args;
    char q[] = "/quit";
    printf("socket desc %d from room(thread) number %d\n", room->clientList.clients[0].socketDescriptor, room->room_num);
    printf("client name: %s, client's descriptor: %d\n", room->clientList.clients[0].Name, room->clientList.clients[0].socketDescriptor);
    while(room->clientsNum > 0){
       
        char buf[BUF_LEN];
        room->readBuffer(room->clientList.clients[0],buf);
        //readBuffer(&room->clientList.clients[0],buf);
        printf("after buf is %s\n", buf);
        break;
        int len = read(room->clientList.clients[0].socketDescriptor, buf, BUF_LEN);
        if(len < sizeof(buf) && len > 0){
            buf[len] = 0;
            if(strcmp((const char*)buf, "/quit\0") == 0){
                printf("QUIT: entered quit\n");
                break;
            }
            printf("name -> %s, descriptor -> %d\n",room->clientList.clients[1].Name,room->clientList.clients[1].socketDescriptor);
            write(room->clientList.clients[1].socketDescriptor, buf, strlen(buf));
            //printf("%s: %s", room->clientList.clients[0].Name, buf);
            len = 0;
            memset(buf,0,BUF_LEN);
        }
        
        
            
        
    }

    pthread_mutex_lock (&room->roomMtx);
    //free(room->client);
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
        printf("socket desc -> %d\n", cl.socketDescriptor);

            char buf[BUF_LEN];
            //readBuffer(&cl, buf);
            
        int len = read(cl.socketDescriptor, buf, BUF_LEN);
        if(len < sizeof(buf)){
            buf[len] = 0;
        }
        printf("buf after client connected is -> %s\n", buf);
        
        //parsing the client's initial connection msg, specify the client's name and the room number
        char* sep = strtok(buf,":");
        cl.Name = sep;
        sep = strtok(NULL, ":");
        cl.roomNumber = atoi(sep);

        cl.ip = getipaddr(clientAddr.sin_addr.s_addr, &cl.ipLen);
        
            if(rooms[cl.roomNumber-1].isActive == 0){
                printf("entered the condition\n");
                chatroomInit(&rooms[cl.roomNumber-1], cl, &routine);
                printf("after thread initialized\n");
            }
            else{
                chatroomAdd(&rooms[cl.roomNumber-1],cl);
            }
        
        
        

    }
        
    
    


}
