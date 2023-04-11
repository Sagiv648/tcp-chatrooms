#ifndef _GROUP_H_
#define _GROUP_H_
#include "utils.hpp"
#include "packet.hpp"



class Client;


class Group
{
private:
    std::vector<std::shared_ptr<Client>> clients;
    
    std::string name;
    
    

public:
    
    Group(std::string name);
    ~Group();
    std::string getName();
    
    std::vector<std::shared_ptr<Client>>& getClients();

};

#endif