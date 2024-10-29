#ifndef __SERVER_ENGINE_HPP__
# define __SERVER_ENGINE_HPP__
# include "Server.hpp"

# include <sys/epoll.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <cstring>
# include <vector>
# include <iostream>

# define MAX_EVENTS 10  // nombre maximum d'événements à gérer simultanément
                        // à récupérer de la config

typedef std::vector<struct epoll_event> t_events;
typedef std::vector<Server> Servers;
typedef struct epoll_event t_event;

class ServerEngine
{
    private:
        int                 epollFd;
        t_event             event;
        int                 maxEvents;
        std::vector<int>    serverFds;
        //on doit ajouter une vector de clients
        //comme ça on concatene ce que nous avons lu
        //de chaque requete de chaque cleint

    public:
        ServerEngine(void);
        ~ServerEngine(void);
        ServerEngine(int maxEvents);
        void    setupServers(Servers &servers);
        int     setupServer(Server &server);
        void    mainLoop(void);
        int     isServer(int fd);
        void    acceptNewConnection(int serverFd);
        void    handleClient(int clientFd);
};

#endif