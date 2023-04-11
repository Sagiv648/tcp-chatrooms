#ifndef _CLIENT_H_
#define _CLIENT_H_
#include "utils.hpp"


class Group;

class Client
{
private:
    std::shared_ptr<Group> group;
    std::shared_ptr<pollfd> pollfdEntry;
    std::string username;
    

public:
    
    Client(int socketDescriptor);
    Client();
    ~Client();
    std::shared_ptr<pollfd> getFdEntry();
    void setDescriptorEntry(int newDescriptor);
    std::string getUsername();
    void setUsername(std::string name);
    std::shared_ptr<Group> getGroup();
    void setGroup(std::shared_ptr<Group> group);
};


#endif