#ifndef __REQUEST_HPP__
# define __REQUEST_HPP__

# include "RequestParser.hpp"
# include <iostream>
# include <map>
# include <algorithm>
# include <cctype>

# define RESET "\033[0m"
# define RED "\033[031m"
# define GREEN "\033[032m"
# define YELLOW "\033[033m"
typedef std::string String;
typedef std::map<String, String> Map;

class HttpRequest
{
	private:
		/*------------- attributes -------------*/
		int     		socketFd;
		short   		status;
		String  		path;
		String			wholeRequest;
		String  		requestBody;
		Map				queryVars;
		Map				requestFields;
		RequestParser	parser;

		/*------------- Private methods -------------*/
		// initFields(void);

	public:
		HttpRequest(const HttpRequest& request);
		HttpRequest& operator=(const HttpRequest& request);
		HttpRequest(void);
		/*------------- Public methods -------------*/
		~HttpRequest(void);
		HttpRequest(int socketFd);
// 		readFromSocket(void);
// 		parseRequest(void);
};

#endif
