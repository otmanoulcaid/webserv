#ifndef __GET_HPP__
#define __GET_HPP__

#include "Post.hpp"

class Get
{
	public:
		Request							&request;
		t_response_phase				&__responsePhase;

		RessourceExplorer				*explorer;
		Location						*location;
		Server							*server;

		std::ifstream					__file;

		void							readFile(void);
		void							autoIndexing(void);
		bool							authenticated();
		void							getInPhase(BasicString &body);
		void							duringGetPhase(BasicString &body);

	public:
		t_get_phase 					__phase;

		void							reset();
		void							setWorkers(RessourceExplorer &explorer, Location &location, Server &server);
		void							executeGet(BasicString &body);

		Get(Request &request, t_response_phase &phase);
		Get(const Get &copy);
		Get &operator=(const Get &assign);
		~Get();
};

std::ostream &operator<<(std::ostream &o, Get const &r);

#endif