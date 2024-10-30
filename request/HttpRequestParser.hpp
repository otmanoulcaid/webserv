#ifndef __HTTP_REQUEST_PARSER__
# define __HTTP_REQUEST_PARSER__

# include <iostream>
# include <algorithm>
# include <string>
typedef std::string String;

class HttpRequestParser
{
	private:
		/*------------- attribute -------------*/
		String  requestContent;

		/*------------- Private Methods -------------*/

	public:
		/*------------- Public Methods -------------*/
		HttpRequestParser(void);
		HttpRequestParser(const HttpRequestParser& request);
		HttpRequestParser&   operator=(const HttpRequestParser& request);
		HttpRequestParser(String& request);
		~HttpRequestParser(void);
		void    setrequestContent(String& request);
		// String& firstLine(void);
		// String& nextLine(void);
		// String& getKey(void);
		// String& getValue(void);
		// int     validField(void);
		// int     validKey(void);
		// int     validValue(void);
		// String& nextShunk(void);
		// String& getBody(void);
};

#endif