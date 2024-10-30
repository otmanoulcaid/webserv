#ifndef __CLIENT_HPP__
# define __CLIENT_HPP__

# include <string>
# include <iostream>

class Client
{
private:
    int         fd;
    std::string buffer;
    
public:
    Client(/* args */);
    Client(int fd);
    ~Client();
    std::string getBuffer(void);
    void        appendBuffer(std::string buffer);
};


#endif