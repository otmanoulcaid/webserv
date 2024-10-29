#include "ServerEngine.hpp"

int main()
{
    ServerEngine engine(10);
    Servers servers;
    Server server;

    servers.push_back(server);
    engine.setupServers(servers);
    engine.mainLoop();
    return 0;
}