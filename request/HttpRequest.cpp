#include "HttpRequest.hpp"

HttpRequest::HttpRequest(void)
{
    std::cout << "HttpRequest default constructor called\n";
}

HttpRequest::~HttpRequest(void)
{
    std::cout << "HttpRequest destructor called\n";
}

HttpRequest::HttpRequest(int socket):
socketFd(socket),
status(200),
path(""),
wholeRequest("")
{
    std::cout << "HttpRequest Param constructor called\n";
}