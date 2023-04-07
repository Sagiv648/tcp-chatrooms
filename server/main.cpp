
#include <iostream>
#include "utils.hpp"




sockaddr_in addr;

int main(int argc, char** argv){

    int socketFD = setupServer(addr);
    if(socketFD == -1)
        exit(EXIT_FAILURE);

    std::cout << "We listen...\n";
    
    char buf[] = "Hello world1";
    char reads[20];

    memset(reads,0,sizeof(reads));
    for(;;)
    {
        int connected = accept(socketFD,NULL,NULL);
        if(connected)
        std::cout << "We connected with someone\n";
        int written = write(connected,buf,sizeof(buf));

        

        
            int b = read(connected,reads,sizeof(reads));
            printf("We read %s from the socket\n", reads);
            int c = read(connected,reads,sizeof(reads));
            printf("We read %s from the socket\n", reads);
            int d = read(connected,reads,sizeof(reads));
            printf("We read %s from the socket\n", reads);

        
        
    }

    
    // initRooms(rooms, &routine);

    // serverSocketDesc = socket(AF_INET, SOCK_STREAM,0);
    // if(serverSocketDesc == -1){
    //     perror("Failed to create a socket.\n");
    //     exit(1);
    // }

    // setServerAddr(&serverAddr);
    
    // if(bind(serverSocketDesc,(struct sockaddr*)&serverAddr, sizeof(serverAddr)) != 0 ||
    //     listen(serverSocketDesc, 100) != 0){
    //         perror("error occured with server\n");
    //         exit(1);
    //     }
    // printf("Server is listening.\n");
    // struct sockaddr_in clientAddr;
    // socklen_t clientAddrLen;
    // memset(&clientAddr, 0, sizeof(clientAddr));
    // client cl;

    // while(1){

    //     cl.socketDescriptor = accept(serverSocketDesc,(struct sockaddr*)&clientAddr,&clientAddrLen);
    //     char buf[BUF_LEN];
    //     int len = read(cl.socketDescriptor, buf, BUF_LEN-1);
    //     if(len < sizeof(buf)){
    //         buf[len] = 0;
    //     }
        
    //     char* sep = strdup(strtok(buf,":"));
    //     cl.Name = sep;
    //     sep = strtok(NULL, ":");
    //     cl.roomNumber = atoi(sep);

    //     cl.ip = getipaddr(clientAddr.sin_addr.s_addr, &cl.ipLen);
    //     printf("connected details:\n");
    //     printf("Name: %s, room number: %d, socket descriptor: %d\n",cl.Name,cl.roomNumber,cl.socketDescriptor);

    //     pthread_mutex_lock(&(rooms[cl.roomNumber-1].roomMtx));
    //     if(rooms[cl.roomNumber-1].clientsNum == 0){
    //         printf("signaling from main\n");
    //         pthread_cond_signal(&(rooms[cl.roomNumber-1].roomCond_v));
    //     }
    //     chatroomAdd(&(rooms[cl.roomNumber-1]),cl);
        
    //     pthread_mutex_unlock(&(rooms[cl.roomNumber-1].roomMtx));
        
        
    //     memset(buf,0,BUF_LEN);
        
        
        

    }
        
    
    



