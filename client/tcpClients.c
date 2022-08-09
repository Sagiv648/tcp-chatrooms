#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include "client_det.h"


void* recieveMsg(void* arg){

    client* cl = (client*)arg;

    while(cl->connected){

        int num_read = read(cl->socketFD, cl->incomingBuffer, sizeof(cl->incomingBuffer));
        if(num_read > 0){
            cl->incomingBuffer[num_read] = 0;
            fputs(cl->incomingBuffer,stdout);
        }
    }

}

void userInput(char* inputBuffer);

char* getRoom();

void getUserName(char* input);

char* writeBuffer();

int main(int argc, char**argv){

    

    client me;


    pthread_t incoming_msg;
    struct sockaddr_in server;
    int client = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server,0,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(2000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    char inputBuffer[51];
    getUserName(inputBuffer);
    char* room = getRoom();
    
    initClient(&me, client, inputBuffer, atoi(room));

    memset(inputBuffer,0,sizeof(inputBuffer));
    strcat(inputBuffer, me.userName);
    strcat(inputBuffer, ":");
    strcat(inputBuffer, room);

    free(room);
    printf("input buffer -> %s\n", inputBuffer);

    if(connect(client,(struct sockaddr*)&server,(socklen_t)sizeof(struct sockaddr_in)) != -1){
        
        if(write(client,inputBuffer,strlen(inputBuffer)) == -1){
            perror("Error occured\n");
            exit(1);
        }
        else{
            printf("sent -> %s\n", inputBuffer);
        }
        memset(inputBuffer,0,sizeof(inputBuffer));
        me.connected = 1;


        
        pthread_attr_t det;
        pthread_attr_init(&det);
        pthread_attr_setdetachstate(&det, PTHREAD_CREATE_DETACHED);
        pthread_create(&incoming_msg, &det, &recieveMsg, (void*)&me);
        

        while(1){

            userInput(inputBuffer);
            int num_written = write(me.socketFD, inputBuffer, strlen(inputBuffer));

            if(strcmp((const char*)inputBuffer, "/quit") == 0){

                me.connected = 0;
                close(me.socketFD);

                break;
            }

        }
        
    }
    else{
        printf("Error with connection.\n");
        return 1;
    }
    
    
    return 0;
}

void userInput(char* inputBuffer){

    memset(inputBuffer,0,sizeof(inputBuffer));

    printf("$ ");

    fgets(inputBuffer, sizeof(inputBuffer)-1, stdin);
    printf("\n");
    
}
char* getRoom(){

    int isCorrect = 0;
    char* buf = malloc(5*sizeof(char));

    while(!isCorrect){
        printf("Enter the chat room number: (1 - 2)");
        fgets(buf,5,stdin);
        buf[strlen(buf)-1] = 0;
        int i;
        for(i = 0; *(buf+i); i++){
            
            if(*(buf+i) < '0' || *(buf+i) > '9'){
                break;
            }
        }
        printf("%s\n", buf);

        if(!*(buf+i)){
            int boundaryTest = atoi(buf);
            if(boundaryTest >= 1 || boundaryTest <= 200){
                printf("buf here %s\n", buf);
                break;
            }

            
        }
    }
    return buf;
}

void getUserName(char* input){

    printf("Enter your username:");
    fgets(input, 20, stdin);
    input[strlen(input)-1] = 0;
    
}

char* writeBuffer(){
    
    int len = 1;
    char* buf = (char*)malloc(sizeof(char)*len);
    int ch;

    // if(fgets(buf, len, stdin) != NULL){
        
    //     buf[strlen(buf)-1] = 0;
    //     return buf;
    // }


    while( (ch = getchar()) && ch != '\n' && ch != EOF && len < BUF_LEN ){
        
        *(buf+(len-1)) = ch;
        
        char* tmp = realloc(buf, sizeof(char)*(++len));
        if(!tmp){
            perror("error with mem");
            exit(1);
        }
        buf = tmp;
        tmp = NULL;
    }
    *(buf+(len-1)) = 0;
    //memset(stdin->_IO_write_end, 0, len);
    
    
    return buf;
    // while( len < BUF_LEN && (ch = getchar()) && ch != '\n' && ch != EOF  ){

    //     buffer[len++] = (char)ch;
    //     if(len == BUF_LEN) break;
        
    // }
    // buffer[len] = 0;
    
    //memcpy(buffer,buf,len);
    //strcpy(buffer,buf);
}