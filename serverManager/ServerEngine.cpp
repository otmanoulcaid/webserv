#include "ServerEngine.hpp"

ServerEngine::ServerEngine(void)
{
    // std::cout << "ServerEngine default constructor appellé\n";
}

ServerEngine::~ServerEngine(void)
{
    // std::cout << "ServerEngine destructor appellé\n";
}


ServerEngine::ServerEngine(const ServerEngine& engine)
{
    // std::cout << "copy constructor appellé" << std::endl;
    *this = engine;
}

ServerEngine& ServerEngine::operator=(const ServerEngine& engine)
{
    if (this != &engine)
    {
        this->maxEvents = engine.maxEvents;
        this->epollFd = engine.epollFd;
        // à implementer
    }
    return (*this);
}

ServerEngine::ServerEngine(int maxEvents) :
maxEvents(maxEvents),
epollFd(0)
{
    std::cout << "ServerEngine Param constructor called\n";
    this->maxEvents = maxEvents;
}

void    ServerEngine::setupServers(Servers &servers)
{
    for (Servers::iterator it = servers.begin(); it != servers.end(); ++it)
    {
        int server_fd = setupServer(*it);
        if (server_fd == -1) {
            perror("Erreur lors de la récupération du socket du serveur");
            exit(1);
        }
        pollfd pfd;
        pfd.fd = server_fd;
        pfd.events = POLLIN;
        events.push_back(pfd);
    }
}

int    ServerEngine::setupServer(Server &server)
{
    int serverFd;
    struct sockaddr_in address;

    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == -1)
        return (perror("Erreur lors de la création du socket"), -1);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    //address.sin_port = htons(server.getPort()); // à recuperer de la config
    address.sin_port = htons(9000);
    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) == -1)
        return (perror("Échec du bind"), close(serverFd), -1);
    if (listen(serverFd, 3) < 0)
        return (perror("Erreur lors du listen"), close(serverFd), -1);
    this->serverFds.push_back(serverFd);
    return serverFd;
}


//poll return the number of events (file descriptors) ready for reading or wrriting
void    ServerEngine::mainLoop(void)
{
    std::cout << "\33[32m" << "WEBSERV waiting for connection...\n" << "\33[0m";
    while (true)
    {
        int num_fds = poll(events.data(), events.size(), -1);
        if (num_fds == -1)
        {
            perror("Erreur lors de poll");
            continue;
        }
        for (size_t i = 0; i < this->events.size() && num_fds > 0; ++i)
        {
            if (events[i].revents & POLLIN)
            { 
                if (std::find(this->serverFds.begin(), this->serverFds.end(), events[i].fd)\
                    != this->serverFds.end())
                    acceptNewConnection(events[i].fd);
                else
                    readFromClient(this->events[i].fd);
                num_fds--;
            }
        }
    }
}

void ServerEngine::acceptNewConnection(int serverFd)
{
    int newSocket = accept(serverFd, NULL, NULL);
    if (newSocket == -1)
    {
        perror("Erreur lors de l'accept");
        return;
    }
    pollfd clientFd;
    clientFd.fd = newSocket;
    clientFd.events = POLLIN;
    this->events.push_back(clientFd);
    this->clients[newSocket] = Client(newSocket);
}

void    ServerEngine::readFromClient(int clientFd)
{
    char buffer[1024];
    ssize_t bytes_read = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read == -1)
        perror("Erreur de lecture");
    else if (bytes_read <= sizeof(buffer) - 1) /*terminer la lecture de la requete*/
    {
        buffer[bytes_read] = '\0';
        this->clients[clientFd].appendBuffer(buffer);
        this->handleClient(clientFd);
    }
    else
    {
        buffer[bytes_read] = '\0';
        this->clients[clientFd].appendBuffer(buffer);
        memset(buffer, sizeof(buffer), 0);
    }
}

void    ServerEngine::handleClient(int fd)
{
        //parser la requette
    requestParser.setClient(&clients[fd]);
    requestParser.parseRequest();
        //envoyer la reponse
    const char* response = "HTTP/1.1 200 OK\n"
                        "Content-Type: text/html\n"
                        "Content-Length: 21\n"
                        "Connection: keep-alive\n\n"
                        "<h1>Hello world!</H1>"; //hh khdama wakha hakkak <h1></H1>
    send(fd, response, strlen(response), 0);
    // close(fd); //si le client want to let the socket open for future connections sinon on ferme le fd
    std::cout << CYAN << " response sent to client " << RESET << fd << std::endl;
}
