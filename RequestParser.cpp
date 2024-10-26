#include "RequestParser.hpp"

RequestParser::RequestParser(void)
{
    std::cout << "RequestParser default constructor called\n";
}

RequestParser::~RequestParser(void)
{
    std::cout << "RequestParser destructor called\n";
}

RequestParser::RequestParser(String& requestContent) : requestContent(requestContent)
{
    std::cout << "RequestParser Param constructor called\n";
}

void    RequestParser::setrequestContent(String& request)
{
    this->requestContent = request;
}