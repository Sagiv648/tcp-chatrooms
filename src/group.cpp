#include "./../include/group.hpp"




Group::Group(std::string name)
{
    this->name = name;
    clients = std::vector<std::shared_ptr<Client>>();
}

Group::~Group()
{
    
}
std::string Group::getName()
{
    return name;
}
std::vector<std::shared_ptr<Client>>& Group::getClients()
{
    return clients;
}
