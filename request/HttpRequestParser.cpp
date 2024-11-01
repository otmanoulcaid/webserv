#include "HttpRequestParser.hpp"

HttpRequestParser::HttpRequestParser(void) :
client(NULL)
{
	// std::cout << "HttpRequestParser default constructor called\n";
}

HttpRequestParser::~HttpRequestParser(void)
{
	// std::cout << "HttpRequestParser destructor called\n";
}

HttpRequestParser::HttpRequestParser(const HttpRequestParser& request)
{
	*this = request;
}

HttpRequestParser&	HttpRequestParser::operator=(const HttpRequestParser& request)
{
	if (this != &request)
		this->client = request.client;
	return *this;
}
		

void    HttpRequestParser::setClient(Client *client)
{
	this->client = client;
}

void HttpRequestParser::parseFirstLine(String& line) 
{
	(void)line;
	return ;
}

void HttpRequestParser::parseLineHeaders() 
{
	return ;
}

void HttpRequestParser::parseRequest()
{
	String line = this->getFirstLine();
	std::cout << RED << line << RESET << std::endl;
	parseFirstLine(line);
	while (!(line = this->nextLine()).empty() && client->getStatus() == 200)
	{
		std::cout << RED << line << RESET << std::endl;
		parseLineHeaders();
	}
}

String HttpRequestParser::getFirstLine()
{
	size_t pos = client->getBuffer().find("\r\n");
	String line = client->getBuffer().substr(0, pos);
	client->erase(pos + 2);  // Erase up to the end of "\r\n"
	return line;
}

String HttpRequestParser::nextLine()
{
	size_t pos = client->getBuffer().find("\n");
	if (pos == std::string::npos )
		return "";  // No newline found, return empty
	String line = client->getBuffer().substr(0, pos);
	client->erase(pos + 1);  // Erase up to the end of "\n"
	return line;
}

int     HttpRequestParser::parseHeaderLine(String& line)
{
	String key;
	String value;
	size_t pos = line.find(":");
	if (pos == std::string::npos)
		return 0;
	key = line.substr(0, pos);
	value = line.substr(pos + 1);
	std::cout << "Key: " << key << " Value: " << value << std::endl;
	if (!validKey(key) || !validValue(value))
		return 0;
	this->client->setHeader(key, value);
	return 1;
}

int     HttpRequestParser::validKey(String& key)
{
	(void)key;
	return 1;
}

int     HttpRequestParser::validValue(String& value)
{
	(void)value;
	return 1;
}

int     HttpRequestParser::isChunked(void)
{
	String transferEncoding = this->client->getHeader("Transfer-Encoding");
	if (transferEncoding.empty())
		return 0;
	if (transferEncoding == "chunked")
		return 1;
	return 0;
}

String& HttpRequestParser::nextShunk(void)
{
	size_t pos = client->getBuffer().find("\r\n");
	if (pos == std::string::npos)
		return "";  // No newline found, return empty
	String chunk = client->getBuffer().substr(0, pos);
	client->erase(pos + 2);  // Erase up to the end of "\r\n"
	return chunk;
}

void    HttpRequestParser::parseBody(void)
{
	String body;
	if (isChunked())
	{
		String chunk;
		while (!(chunk = nextShunk()).empty())
			body += chunk;
	}
	else
	{
		size_t pos = client->getBuffer().find("\r\n\r\n");
		if (pos == std::string::npos)
		{
			//check in RFC if this case return 400 status code
			this->client->setBody("");
			return ;
		}
		body = client->getBuffer().substr(0, pos);
		client->erase(pos + 4);  // Erase up to the end of "\r\n\r\n"
	}
	this->client->setBody(body);
}
