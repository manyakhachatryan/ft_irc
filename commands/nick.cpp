# include "../Server.hpp"

void Server::nick_cmd(std::string cmd, int fd) 
{
    std::vector<std::string>  splited =  split(cmd, ' '); 
    if (splited.size() == 2)
    {
        for (std::map<int, Client*>::iterator it = Clients.begin(); it != Clients.end(); ++it)
        {
            if(it->second->getNickname() == splited[1]  && it->first!=fd)
            {
                sendMyMsg(fd, ERR_NICKNAMEINUSE(splited[0], splited[1])); 
                return;
            } 
        }
    }
   if (splited.size() < 2)
    {
        sendMyMsg(fd,  ERR_NEEDMOREPARAMS(Clients[fd]->getPrefix(),splited[0])); 
        return ;
    }  
    if (splited.size() > 2)
    {
        sendMyMsg(fd,  ERR_NEEDLESSPARAMS(Clients[fd]->getPrefix(),splited[0])); 
        return ;
    }   
    Clients[fd]->setNickname(splited[1]);
}