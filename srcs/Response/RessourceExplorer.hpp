#pragma once

// # include "../webserv.hpp"
# include "../Request/Request.hpp"

class RessourceExplorer
{
	private:
		void			loadType(const char* path);

	public:
		t_type			__type;
		String			__fullPath;
		Location		*__location;

		void			changeRequestedFile(String file);
		void			loadPathExploring(const String& uri);
		void			prepareRessource(Location& location, const String& uri);

		RessourceExplorer();
		RessourceExplorer(const RessourceExplorer &copy);
		RessourceExplorer &operator=(const RessourceExplorer &assign);
		~RessourceExplorer();
};

std::ostream &operator<<(std::ostream &o, RessourceExplorer const &r);
