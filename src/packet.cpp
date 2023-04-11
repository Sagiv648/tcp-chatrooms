#include "./../include/packet.hpp"
#include <iostream>



Packet::Packet(std::shared_ptr<Client> cl, char *headers)
{
    client = cl;
    
    std::string str = std::string(headers);


    // 2 types of content: 1) Normal string message, 2) File
    /*  packet header:
        ContentSize:[sz in bytes]\r\n
        -
        Username:[username]\r\n
        -
        Group:[group]\r\n
        -
        File:[Yes/No]\r\n
        -

    */
   /*
        packet message:
        [Content in bytes] (if it's a string message it will come as it is, else it will be a file and will come in file bytes)
   */
    
    char * sep = strtok((char*)str.c_str(), "-");
    std::vector<std::string> fields;
    while(sep)
    {
        fields.push_back(std::string(sep));
        
        fields[fields.size()-1] = fields[fields.size()-1].substr(0,fields.back().length()-4);
        sep = strtok(NULL, "-");
    }
    
    for(size_t i = 0; i < fields.size();i++)
    {
        sep = strtok((char*)fields[i].c_str(),":");
        
        std::vector<std::string> keyVal;
        
        while(sep)
        {
            keyVal.push_back(std::string(sep));
            
            sep = strtok(NULL, ":");
        }
        headersMapping.insert(std::pair<std::string,std::string>(keyVal[0],keyVal[1]));
        std::cout << keyVal[0] << " | " << keyVal[1] <<"\n";
        keyVal.clear();
    }

    cl.get()->setUsername(headersMapping["Username"]);
    
    

}

std::shared_ptr<Client> Packet::getClient()
{
    return client;
}

void Packet::setClient(std::shared_ptr<Client> cl)
{
    client = cl;
}

bool Packet::isFile()
{
    return file;
}

void Packet::setFile(bool file)
{
    this->file = file;
}

uint8_t Packet::getType()
{
    return type;
}

void Packet::setType(uint8_t type)
{
    this->type = type;
}
std::string Packet::getGroupName()
{
    return headersMapping["Group"];
}

size_t Packet::getContentSize()
{
    return std::stoi(headersMapping["ContentSize"]);
}
void Packet::setContent(std::string content)
{
    this->content = content;
}
std::string Packet::getContent()
{
    return content;
}
void Packet::setTime(u_int64_t time)
{
    headersMapping["Time"] = std::to_string(time);
}
u_int64_t Packet::getTime()
{
    return std::stol(headersMapping["Time"]);
}