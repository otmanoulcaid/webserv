#ifndef __SERVER_ENGINE_HPP__
# define __SERVER_ENGINE_HPP__
# include "Server.hpp"
# include "../request/Client.hpp"
# include "../request/HttpRequestParser.hpp" 
# include "../webserv.hpp"
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>

# define MAX_EVENTS 10  // nombre maximum d'événements à gérer simultanément
                        // à récupérer de la config

typedef std::vector<pollfd> t_events;
typedef std::vector<Server> Servers;

class ServerEngine
{
    private:
        int                     epollFd;
        t_events                events;
        int                     maxEvents;
        std::vector<int>        serverFds; 
        std::map<int, Client>   clients; // map des clients pour localiser le client par son fd 
        HttpRequestParser       requestParser;
        //HttpResponse            Response;

    public:
        ServerEngine(void);
        ~ServerEngine(void);
        ServerEngine(int maxEvents);
        ServerEngine(const ServerEngine& engine);
        ServerEngine& operator=(const ServerEngine& engine);
        void    setupServers(Servers &servers);
        int     setupServer(Server &server);
        void    mainLoop(void);
        void    acceptNewConnection(int serverFd);
        void    readFromClient(int clientFd);
        void    handleClient(int fd);
};

#endif