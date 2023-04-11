#include "../include/routines.hpp"
#include "../include/packet.hpp"
#include "../include/group.hpp"
#include <iostream>


size_t vectorSz = 0;
std::vector<Group> chatGroups;


void* workRoutine(void*)
{
   char packetHeader[HEADER_MAX_BYTES] = {0};
    
    while(1)
    {
        if(vectorSz > 0)
        {
            int polled = 0;
            for(size_t i = 0; i < vectorSz; i++)
            {
                size_t clListSz = chatGroups[i].getClients().size();
                std::vector<std::shared_ptr<Client>> clients = chatGroups[i].getClients();
                
                for(size_t j = 0; j < clListSz;j++){
                    int fd = clients[j].get()->getFdEntry().get()->fd;
                    if(fd != -1)
                        polled = poll(clients[j].get()->getFdEntry().get(),1,100);

                    if(polled > 0)
                    {

                        size_t sz = read(fd,packetHeader,sizeof(packetHeader));
                        
                        if(sz == 0)
                        {
                            //Client disconnects
                            printf("Client with descriptor %d disconnected\n", fd);
                            clients[j].get()->getFdEntry().get()->fd = -1;
                            
                            
                        
                        }
                        else 
                        {
                            Packet p = Packet(clients[j],packetHeader);
                            
                            printf("client named %s sent:\n%s\n", clients[j].get()->getUsername().c_str(), packetHeader);



                            memset(packetHeader,0,sizeof(packetHeader));
                            polled = 0;
                        }
                        

                    }

                }
                
            }
        }
        
        

    
    
        
    }
    return NULL;
}

void* listenRoutine(void*)
{
    printf("I'm the listener\n");
   
    
    for(;;)
    {
        int connected = accept(socketFD,NULL,NULL);
        
        acceptClient(connected);

    }

 
}

void acceptClient(int socket)
{

    size_t i = 0;

    char entryHeaderBuf[HEADER_MAX_BYTES] = {0};
    int nRead = read(socket,entryHeaderBuf,HEADER_MAX_BYTES);
    entryHeaderBuf[nRead] = 0;

    
    std::shared_ptr<Client> cl = std::make_shared<Client>(socket);
    Packet packet = Packet(cl,entryHeaderBuf);
    std::cout << "Username: " << cl.get()->getUsername() << "\n";
    for(; i < vectorSz;i++)
    {
        if(chatGroups[i].getName() == packet.getGroupName())
        break;
    }
    if(i == vectorSz)
    {
        std::cout << "We added a new group named: " << packet.getGroupName() << "\n";
        chatGroups.push_back(Group(packet.getGroupName()));
        vectorSz = chatGroups.size();
    }
    cl.get()->setGroup(std::make_shared<Group>(chatGroups[i]));
    chatGroups[i].getClients().push_back(cl);

    
    
}

