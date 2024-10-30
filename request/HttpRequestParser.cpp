#include "HttpRequestParser.hpp"

HttpRequestParser::HttpRequestParser(void)
{
    std::cout << "HttpRequestParser default constructor called\n";
}

HttpRequestParser::~HttpRequestParser(void)
{
    std::cout << "HttpRequestParser destructor called\n";
}

HttpRequestParser::HttpRequestParser(String& requestContent) : requestContent(requestContent)
{
    std::cout << "HttpRequestParser Param constructor called\n";
}

void    HttpRequestParser::setrequestContent(String& request)
{
    this->requestContent = request;
}