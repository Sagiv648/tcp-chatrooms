#include "../include/client.hpp"
#include "../include/client.hpp"




Client::Client(int socketDescriptor)
{
    pollfdEntry = std::make_shared<pollfd>();

   
    pollfdEntry.get()->fd = socketDescriptor;

    
    pollfdEntry.get()->events = POLLIN;
}
Client::Client()
{
    
}
Client::~Client()
{
    
}
std::shared_ptr<pollfd> Client::getFdEntry()
{
    return pollfdEntry;
}
void Client::setDescriptorEntry(int newDescriptor)
{
    pollfdEntry->fd = newDescriptor;
}
std::string Client::getUsername()
{
    return username;
}
void Client::setUsername(std::string name)
{

   
    username = name;
} 
std::shared_ptr<Group> Client::getGroup()
{
    return group;
}

void Client::setGroup(std::shared_ptr<Group> group)
{
    this->group = group;
}
