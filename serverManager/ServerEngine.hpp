#ifndef __SERVER_ENGINE_HPP__
# define __SERVER_ENGINE_HPP__
# include "Server.hpp"
# include "../request/Client.hpp"
# include "../request/HttpRequestParser.hpp" 
# include "../webserv.hpp"

# include <sys/epoll.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>

# define MAX_EVENTS 10  // nombre maximum d'événements à gérer simultanément
                        // à récupérer de la config

typedef std::vector<struct epoll_event> t_events;
typedef std::vector<Server> Servers;
typedef struct epoll_event t_event;

class ServerEngine
{
    private:
        int                     epollFd;
        t_event                 event;
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