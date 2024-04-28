#include "../Server.hpp"

void Server::who_cmd(std::string cmd, int fd)
{  
    if(!isClientFull(fd))
    {
        sendMyMsg(fd,  ERR_NOTREGISTERED(Clients[fd]->getPrefix()));
        return; 
    }

    std::vector<std::string>  splited =  split(cmd, ' '); 

    if (splited.size() < 2)
    {
        sendMyMsg(fd,   ERR_NEEDMOREPARAMS(Clients[fd]->getPrefix(), splited[0])); 
        return ;
    }      

    if (splited[1][0] == '#' || splited[1][0] == '&')
    {
        if(Channels.find(splited[1]) == Channels.end())   
        {
            sendMyMsg(fd, ERR_NOSUCHCHANNEL(Clients[fd]->getPrefix(),splited[1])); 
            return;
        }

        std::vector<int>::iterator it = std::find(Channels[splited[1]]->clients.begin(), Channels[splited[1]]->clients.end(), fd);
        if(it == Channels[splited[1]]->clients.end())
        {
            sendMyMsg(fd, ERR_NOTONCHANNEL(Clients[fd]->getPrefix(),splited[1])); 
            return;
        }
        for(std::vector<int>::iterator it = Channels[splited[1]]->clients.begin(); it != Channels[splited[1]]->clients.end(); ++it)
        {  
            if(*it!=fd)
            {
            std::cout<<"STEXXXXX"<<std::endl;
                
               // sendMyMsg(fd, RPL_WHOREPLY(Clients[fd]->getNickname(), splited[1], Clients[*it]->getUsername(), Clients[*it]->_hostname  ,Clients[*it]->getNickname(), " ", " "));
            }
        }

    }
    else
    {
       for (std::map<int, Client*>::iterator it = Clients.begin(); it != Clients.end(); ++it) 
        {
            if (splited[1] == it->second->getNickname() && it->first != fd)
            {

                  // ete gtela gtac useri info cuyc tal
                return ;
            }
        }
        sendMyMsg(fd, ERR_NOSUCHNICK(Clients[fd]->getPrefix(), splited[1]));
        return;
    }
}
