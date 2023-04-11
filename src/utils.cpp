#include "../include/utils.hpp"
#include <iostream>

int setupServer(sockaddr_in& addr)
{
    
    int socketFD = socket(PF_INET, SOCK_STREAM,IPPROTO_TCP);
    if(socketFD == -1)
    {
        perror("Cannot create socket");
        return -1;
    }
    int option = SO_REUSEADDR;
    int opt = setsockopt(socketFD,SOL_SOCKET ,SO_REUSEADDR,&option,sizeof(option));
    if(opt == -1)
    {
        perror("Cannot set options to socket");
        return -1;
    }

    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int binded = bind(socketFD,(sockaddr*)&addr,sizeof(addr));
    if(binded == -1)
    {
        perror("Cannot bind socket");
        close(socketFD);
        return -1;
    }
    
    int listening = listen(socketFD,100);
    if(listening == -1)
    {
        perror("Cannot listen");
        close(socketFD);
        return -1;
    }

    return socketFD;
}


