#include "Response.hpp"

// Default constructor
// Response::Response()
// {
//     wsu::info("Response Default Constructor");
// }

Response::Response(Location& location, RessourceExplorer explorer, Request& request, Server& server):
__location(location),
__explorer(explorer),
__request(request),
__server(server)
{
	__state = false;
    wsu::info("Response Parameterized Constructor");
}

Response::~Response()
{
    wsu::info("Response Destructor");
}

Response::Response(const Response& copy):
__location(copy.__location),
__explorer(copy.__explorer),
__request(copy.__request),
__server(copy.__server),
__state(copy.__state) {
    wsu::info("Response Copy Constructor");
}

Response& Response::operator=(const Response& copy) {
    wsu::info("Response Copy Assignment Operator");
    if (this != &copy)
	{
        __state = copy.__state;
        __explorer = copy.__explorer;
    }
    return *this;
}
