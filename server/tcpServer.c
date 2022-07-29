#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include <pthread.h>

struct sockaddr_in serverAddr;
int serverSocketDesc = -1;



int main(int argc, char** argv){
    
    serverSocketDesc = socket(AF_INET, SOCK_STREAM,0);
    if(serverSocketDesc == -1){
        perror("Failed to create a socket.\n");
        exit(1);
    }
    setServerAddr(&serverAddr);
    
    if(bind(serverSocketDesc,(struct sockaddr*)&serverAddr, sizeof(serverAddr))!= 0 &&
        listen(serverSocketDesc, 100) != 0){
            perror("error occured with server\n");
            exit(1);
        }
    printf("Server is listening.\n");
    
    


}
