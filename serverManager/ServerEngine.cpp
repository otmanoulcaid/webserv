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
    this->epollFd = epoll_create1(0);
    if (this->epollFd == -1) {
        perror("Erreur lors de la creation de l'instance epoll");
        exit(1);
    }
}

void    ServerEngine::setupServers(Servers &servers)
{       
    for (Servers::iterator it = servers.begin(); it != servers.end(); ++it)
    {
        this->event.data.fd = setupServer(*it);
        if (event.data.fd == -1) {
            perror("Erreur lors de la récupération du socket du serveur");
            close(this->epollFd);
            exit(1);
        }
        this->event.events = EPOLLIN;
        if (epoll_ctl(this->epollFd, EPOLL_CTL_ADD, this->event.data.fd, &this->event) == -1) {
            perror("Erreur lors de l'ajout du serveur à epoll");
            close(this->event.data.fd);
            close(this->epollFd);
            exit(1);
        }
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

void    ServerEngine::mainLoop(void)
{
    std::cout << "\33[32m" << "WEBSERV waiting for connection...\n" << "\33[0m";
    std::vector<struct epoll_event> events(this->maxEvents);
    while (true)
    {
        int num_fds = epoll_wait(this->epollFd, events.data(), MAX_EVENTS, -1);
        if (num_fds == -1)
        {
            perror("Erreur lors de epoll_wait");
            continue;
        }
        for (int i = 0; i < num_fds; i++)
        {
            if (std::find(this->serverFds.begin(), this->serverFds.end(),\
                events[i].data.fd) != this->serverFds.end()) //check if the fd is a server socket
                acceptNewConnection(events[i].data.fd);
                //!!! ajouter ce nouveau client a la liste des clients
            else
                //pour gerrer l'un des descripteurs de fichiers des clients
                readFromClient(events[i].data.fd);
        }
    }
}

void    ServerEngine::acceptNewConnection(int serverFd)
{
    int newSocket = accept(serverFd, NULL, NULL);
    if (newSocket == -1)
    {
        perror("Erreur lors de l'accept");
        return ;
    }
    this->event.data.fd = newSocket;
    this->event.events = EPOLLIN;
    if (epoll_ctl(this->epollFd, EPOLL_CTL_ADD, newSocket, &this->event) == -1)
    {
        perror("Erreur lors de l'ajout du nouveau socket à epoll");
        close(newSocket);
    }
    this->clients[newSocket] = Client(newSocket);
}

void    ServerEngine::readFromClient(int clientFd)
{

    char buffer[1024];
    ssize_t bytes_read = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read == -1)
    {
        perror("Erreur de lecture");
        close(clientFd);
        epoll_ctl(this->epollFd, EPOLL_CTL_DEL, clientFd , NULL);
    }
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
    send(fd, "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!", 72, 0);
        // std::cout << "Client request: " << this->clients[fd].getBuffer() << std::endl;
    close(fd);
    epoll_ctl(this->epollFd, EPOLL_CTL_DEL, fd, NULL);
}
