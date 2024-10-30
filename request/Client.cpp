#include "Client.hpp"


Client::Client(/* args */)
{
}

Client::Client(int fd) : 
fd(fd),
buffer("")
{
}


Client::~Client()
{
}

std::string Client::getBuffer(void)
{
    return this->buffer;
}

void Client::appendBuffer(std::string buffer)
{
    this->buffer += buffer;
}