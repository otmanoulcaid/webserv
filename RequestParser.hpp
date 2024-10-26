#ifndef __REQUEST_PARSER__
# define __REQUEST_PARSER__

# include <iostream>
# include <algorithm>
# include <string>
typedef std::string String;

class RequestParser
{
	private:
		/*------------- attribute -------------*/
		String  requestContent;

		/*------------- Private Methods -------------*/

	public:
		/*------------- Public Methods -------------*/
		RequestParser(void);
		RequestParser(const RequestParser& request);
		RequestParser&   operator=(const RequestParser& request);
		RequestParser(String& request);
		~RequestParser(void);
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