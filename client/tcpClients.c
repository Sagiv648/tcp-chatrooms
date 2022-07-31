#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>




int main(int argc, char**argv){
    struct sockaddr_in server;
    int client = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server,0,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(2000);
    server.sin_addr.s_addr = inet_addr("10.0.2.15");
    

    if(connect(client,(struct sockaddr*)&server,(socklen_t)sizeof(struct sockaddr_in)) != -1){
        printf("connected\n");
        char buf[] = "Xoxo:10";
        write(client, &buf, sizeof(buf));
        
    }
    while(1){
        char bufTest[] = "hello there";
        write(client, bufTest, sizeof(bufTest));
        break;
    }
    
    

   


    return 0;
}