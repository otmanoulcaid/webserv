#ifndef __CGI_HPP__
#define __CGI_HPP__

// # include "../webserv.hpp"
# include "Get.hpp"

class Cgi : public Response
{
	private:
		Request&				__request;
		RessourceExplorer&		__explorer;
		Location&				__location;
        BasicString             __reqBody;
		std::time_t				__start;
		String					__body;
		char					**env;

		void					execute(const char* path, int fd);
		void					readFromPipe(int fd);
		void					setCgiEnvironement();
		void					cgiProcess(void);
		void					clear( void );
		const					char *getMethod();
		String					getQueryString();


	public:
		String& 				 getBody();

		Cgi(RessourceExplorer &explorer, Request &request, Location &location, BasicString &body);
		~Cgi();
		// Cgi(const Cgi &copy);
		// Cgi &operator=(const Cgi &assign);
};

#endif