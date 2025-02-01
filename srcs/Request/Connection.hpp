#ifndef __CONNECTION_HPP__
# define __CONNECTION_HPP__

# include "Request.hpp"
# include "../utilities/BasicString.hpp"

typedef std::map< int, Server* >			t_Server;
typedef std::vector< Server * >				t_serVect;

class Connection
{
	private :
		int								__sd;
		BasicString						__data;
		Request							__request;
		Response						*__response;
		t_Server						*__serversP;
		t_connection_phase			__phase;
		RessourceExplorer				explorer;

		bool 							checkCgi();
		Response*						responseFactory();

		Server							*identifyServer();
		void							processRequest();
		void							identifyWorkers();
		void							processResponse();
		void							processCunkedBody();
		void							initializeTmpFiles();
		void							processDefinedBody();
		void							indentifyRequestBody();
		void							processMultiPartBody();
		void							mpBody( t_multipartsection &part );
		void							mpHeaders( t_multipartsection &part );
		Connection();

	public:
		std::queue< BasicString >		__responseQueue;

		void							addData(const BasicString &input);
		void							setServers( t_Server &servers );
		void							processData();
		int								getSock();


		Connection( int sd );
		Connection( const Connection &copy );
		Connection	&operator=( const Connection &assign );
		~Connection();
};

#endif
