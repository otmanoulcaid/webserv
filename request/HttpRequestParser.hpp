#ifndef __HTTP_REQUEST_PARSER__
# define __HTTP_REQUEST_PARSER__


#include "../webserv.hpp"
#include "Client.hpp"

class HttpRequestParser
{
	public:
		Client	*client;

	public:
		HttpRequestParser(void);
		~HttpRequestParser(void);
		HttpRequestParser(const HttpRequestParser& request);
		HttpRequestParser&	operator=(const HttpRequestParser& request);
		void				setClient(Client *client);
		String				getFirstLine(void);
		void				parseLineHeaders(void);
		void				parseRequest(void);
		void				parseFirstLine(String& line);
		String				nextLine(void);
		int    				parseHeaderLine(String& line);
		int    				validKey(String& key);
		int    				validValue(String& value);
		int     			isChunked(void);
		String				nextShunk(void);
		void				parseBody(void);
};

#endif