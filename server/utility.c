
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"


char** readFromFile(int*len){

    FILE* info;
    char infoBuffer[21];
    info = fopen("../info.env", "r");
    fread(infoBuffer,sizeof(infoBuffer), sizeof(infoBuffer),info);
    fclose(info);
    int i;
    
    int size = 0;
    for(i = 0; i < strlen(infoBuffer);i++ ){
        if(infoBuffer[i] == '='){
            size++;
        }
    }
   char ** buffer = (char**)malloc(sizeof(char*)*size);


   int k = 0;
   for(i = 0; infoBuffer[i] ;i++ ){

        if(infoBuffer[i] == '='){

            i++;
            size = 1;
            char* local = NULL;
            *(buffer+k) = malloc(sizeof(char));

            for(;infoBuffer[i] && infoBuffer[i] != '\n';i++){

                *(*(buffer+k)+(size-1)) = infoBuffer[i];

                local = realloc(*(buffer+k), ++size*sizeof(char));
                if(!local){
                    perror("Not enough memory");
                    exit(0);

                }else{
                    *(buffer+k) = local;
                    local = NULL;
                }
            }
            *(*(buffer+k)+(size-1)) = 0;
            
            k++;
            
        }
    }
    *len =k;
    
    return buffer;
}

void setServerAddr(struct sockaddr_in* addr){
    
    memset(addr,0, sizeof(struct sockaddr_in));
    char** buffer;
    int bufLen;
    buffer = readFromFile(&bufLen);
    
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr(buffer[0]);
    addr->sin_port = htons(atoi(buffer[1]));
    free(buffer);
    
}

uint8_t* getipaddr(uint32_t networkedIP, uint32_t* len){

    uint32_t hostIp = ntohl(networkedIP);
    uint8_t* output = malloc(sizeof(uint8_t)*4);
    memset(output,255,4);
    *len = 4;
    int i;
    for(i = 0; i < 4; i++){
        output[i] &= hostIp;
        hostIp >>= 8;
        
    }
    return output;
}

void readBuffer(client cl,char* incomingBuffer){

    int len = 0;
    int bufLen = 0;
    printf("socket desc %d->",cl.socketDescriptor);
    len = read(cl.socketDescriptor, incomingBuffer, BUF_LEN-1);
    //printf("%s - %d", cl->Name, cl->socketDescriptor);
    // while((len = read(cl.socketDescriptor, incomingBuffer, BUF_LEN)) ){
    //     //printf("buffer now -> %s\n", incomingBuffer);
    //     bufLen += len;
    // }
    incomingBuffer[bufLen] = 0;


}

void recieve(chat_room* room,buffersNode** head){
    int i;
    for(i = 0; i < room->clientsNum; i++){
        enqueBuffer(&head, room->clientList.clients[i].socketDescriptor);
    }
}
void broadcast(chat_room* room, buffersNode** head){
    int i;
    for(i = 0; i < room->clientsNum; i++){
        dequeBuffer(&head, &(room->clientList));
    }
}
