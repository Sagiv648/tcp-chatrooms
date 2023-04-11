#ifndef _PACKET_H_
#define _PACKET_H_
#include "utils.hpp"
#include "client.hpp"


class Packet
{
private:
    std::shared_ptr<Client> client;
    std::map<std::string,std::string> headersMapping;
    std::string content;
    bool file;
    u_int8_t type;
    u_int64_t time;

public:
    
    
    Packet(std::shared_ptr<Client> cl, char * headers);
    std::shared_ptr<Client> getClient();
    void setClient(std::shared_ptr<Client> cl);
    bool isFile();
    void setFile(bool file);
    uint8_t getType();
    void setType(uint8_t type);
    std::string getGroupName();
    size_t getContentSize();
    void setContent(std::string content);
    std::string getContent();
    void setTime(u_int64_t time);
    u_int64_t getTime();
};





#endif