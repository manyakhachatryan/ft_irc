#include "../Server.hpp"

void Server::kick_cmd(std::string cmd, int fd)
{
    if(!isClientFull(fd))
    {
        sendMyMsg(fd,  ERR_NOTREGISTERED(Clients[fd]->getPrefix()));
        return; 
    }
    std::vector<std::string>  splited =  split(cmd, ' '); 
    if (splited.size() !=3 )
    {
        sendMyMsg(fd, ERR_NEEDMOREPARAMS(Clients[fd]->getPrefix(),splited[0]));
        return ;
    } 

    if(Channels.find(splited[1]) == Channels.end())
    {
        sendMyMsg(fd, ERR_NOSUCHCHANNEL(Clients[fd]->getPrefix(),splited[1]));
        return;
    }
    else
    {  
        for(std::vector<int>::iterator it = Channels[splited[1]]->adminIDs.begin(); it != Channels[splited[1]]->adminIDs.end();++it)
        {
            if (fd == *it) 
            {
                for (std::map<int, Client*>::iterator it1 = Clients.begin(); it1 != Clients.end(); ++it1) 
                {
                    if( it1->second->getNickname() == splited[2])
                    {
                        if(it1->first == fd){
                            sendMyMsg(fd, ERR_CANTKICKADMIN(splited[2]));
                            return ;
                        }
                        for(std::vector<int>::iterator it2 = Channels[splited[1]]->clients.begin(); it2 != Channels[splited[1]]->clients.end();++it2)
                        {
                            if(it1->first == *it2)
                            {
                                  std::vector<int>::iterator it3 = std::find(Channels[splited[1]]->adminIDs.begin(), Channels[splited[1]]->adminIDs.end(), it1->first);
                                  if(it3!=Channels[splited[1]]->adminIDs.end())
                                  {
                                        Channels[splited[1]]->adminIDs.erase(it3);
                                  }
                                Channels[splited[1]]->clients.erase(it2);
                                sendMyMsg(it1->first, RPL_KICK(Clients[fd]->getPrefix(), splited[1], it1->second->getNickname()));
                                return;
                            }
                        }
                    }
                }   
            }
        }
        sendMyMsg(fd, ERR_CHANOPRIVSNEEDED(Clients[fd]->getPrefix(), splited[1]));
        return; 
    } 
}