#pragma once

#include "Cgi.hpp"

class Response
{
	protected:
		Location&			__location;
		RessourceExplorer	__explorer;
		Request&			__request;
		Server&				__server;
		bool				__state;

	public:
		Response();
		virtual ~Response();
		Response(const Response& other);
		Response& operator=(const Response& other);
		Response(Location& location, RessourceExplorer explorer, Request& request, Server& server);
		
		virtual BasicString getResponse(BasicString& data) = 0;
};
