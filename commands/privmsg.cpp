#include "../Server.hpp"

void Server::privmsg_cmd(std::string cmd, int fd) 
 {
    if(!isClientFull(fd))
    {
        sendMyMsg(fd,  ERR_NOTREGISTERED(Clients[fd]->getPrefix()));
        return; 
    }
    std::vector<std::string>  splited =  split(cmd, ' '); 
    if (splited.size() == 1)
    {
        sendMyMsg(fd,  ERR_NEEDMOREPARAMS(Clients[fd]->getPrefix(),splited[0]));
        return ;
    } 
    std::string msg = "";
    for(unsigned long i = 2; i < splited.size(); i++)
    {
        msg = msg + splited[i] + " ";
    }
    if(splited[1][0] == '#' || splited[1][0] == '&') 
    {
        if(Channels.find(splited[1]) == Channels.end()) 
        {
            sendMyMsg(fd, ERR_NOSUCHCHANNEL(Clients[fd]->getPrefix(), splited[1]));
            return;
        }
        std::vector<int>::iterator it = std::find(Channels[splited[1]]->clients.begin(), Channels[splited[1]]->clients.end(), fd);
        if(it == Channels[splited[1]]->clients.end())
        {  
            sendMyMsg(fd,  ERR_CANNOTSENDTOCHAN(Clients[fd]->getPrefix(),splited[1]));
            return;
        }
        if (splited.size() == 2)
        {
            sendMyMsg(fd,  ERR_NOTEXTTOSEND(Clients[fd]->getPrefix()));
            return ;
        }
        for(std::vector<int>::iterator it = Channels[splited[1]]->clients.begin(); it != Channels[splited[1]]->clients.end(); ++it)
        {  
            if(*it!=fd)
            sendMyMsg(*it, RPL_MSG(Clients[fd]->getNickname(), "PRIVMSG", splited[1], msg));
        }
    }
    else 
    {
        if (splited.size() == 2)
        {
            sendMyMsg(fd,  ERR_NOTEXTTOSEND(Clients[fd]->getPrefix()));
            return ;
        }
        for (std::map<int, Client*>::iterator it = Clients.begin(); it != Clients.end(); ++it) 
        {
            if (splited[1] == it->second->getNickname() && it->first != fd)
            {
                sendMyMsg(it->first, RPL_MSG(Clients[fd]->getNickname(), "PRIVMSG", splited[1], msg));
                return ;
            }
        }
        sendMyMsg(fd, ERR_NOSUCHNICK(Clients[fd]->getPrefix(), splited[1]));
        return;
    }
}