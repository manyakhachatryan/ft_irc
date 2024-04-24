#include "Client.hpp"
#include <netdb.h>
#include "Server.hpp"
Client::Client(std::string nickName, std::string userName, int fd, struct sockaddr_in address)
{
    std::cout<<"CLIENT CONSSTRUCTOR"<<std::endl;
    _username = userName;
    _nickname = nickName;
    _onlineFD = fd;
    guest = true;
    _pass = false;
    ChannelCount = 0;
    char hostname[NI_MAXHOST];
    getnameinfo((struct sockaddr*)&address, sizeof(address), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV);
    _hostname = hostname;
}

std::string Client::getNickname()
{
    return _nickname;
}

std::string Client::getUsername()
{
     return _username;
}
bool Client::getPass()
{
    return _pass;
}

void Client::setPass(bool pass)
{
    _pass = pass;
}
int Client::getOnlineFD()
{
    return _onlineFD;
}
void Client::setOnlineFD(int fd)
{
    _onlineFD = fd;
}


void Client::setNickname(std::string nickname)
{
    _nickname = nickname;
}

void Client::setUsername(std::string username)
{
    _username = username;
}


const std::string Client::getPrefix()
{
    std::string userName = _username.empty() ? "" : "!" + _username;
    std::string hostName = _hostname.empty() ? "" : "@" + _hostname;

    return _nickname + userName + hostName;
}