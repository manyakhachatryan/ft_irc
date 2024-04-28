# include "../Server.hpp"

void Server::invite_cmd(std::string cmd, int fd)
{
    if(!isClientFull(fd))
    {
        sendMyMsg(fd,  ERR_NOTREGISTERED(Clients[fd]->getPrefix()));
        return;
    }
    std::vector<std::string>  splited =  split(cmd, ' ');
    if (splited.size() != 3)
    {
        sendMyMsg(fd, ERR_NEEDMOREPARAMS(Clients[fd]->getPrefix(),splited[0]));
        return ;
    }
    if(Channels.find(splited[1]) == Channels.end())
    {
        sendMyMsg(fd, ERR_NOSUCHCHANNEL(Clients[fd]->getPrefix(), splited[1])); 
        return;
    }
    else
    {
        for(std::vector<int>::iterator it = Channels[splited[1]]->adminIDs.begin(); it != Channels[splited[1]]->adminIDs.end();++it)
        {
            if (fd==*it) 
            {
                for (std::map<int, Client*>::iterator it1 = Clients.begin(); it1 != Clients.end(); ++it1) 
                {
                    if(it1->second->getNickname() == splited[2])
                    {  
                        std::vector<int>::iterator it2 = std::find(Channels[splited[1]]->clients.begin(), Channels[splited[1]]->clients.end(), it1->first); 
                        if(it2 == Channels[splited[1]]->clients.end())
                        {
                            if ((Channels[splited[1]]->mode_l == true  && Channels[splited[1]]->clients.size() < Channels[splited[1]]->ChatLimit) || Channels[splited[1]]->mode_l == false )
                            {
                                (Channels[splited[1]]->clients).push_back(it1->first);   
                                sendMyMsg(it1->first,  RPL_INVITING(Clients[fd]->getNickname(), Clients[it1->first]->getNickname(), splited[1])); 
                                sendMyMsg(it1->first,  RPL_JOIN(Clients[it1->first]->getNickname(), splited[1])); 
                                if(Channels[splited[1]]->topic=="")
                                    sendMyMsg(it1->first,  RPL_NOTOPIC(splited[1])); 
                                else 
                                    sendMyMsg(it1->first,  RPL_TOPIC(splited[1], Channels[splited[1]]->topic)); 
                                Clients[it1->first]->ChannelCount++;
                                return;
                            }
                            else
                            {
                                sendMyMsg(fd, ERR_CHANNELISFULL(Clients[fd]->getPrefix(), splited[1]));
                                return;
                            }                       
                        } 
                        else 
                        {
                            sendMyMsg(fd,  ERR_USERONCHANNEL(Clients[fd]->getNickname(), Clients[it1->first]->getNickname(), splited[1]));
                            return;
                        }
                    }
                }
                 sendMyMsg(fd, ERR_NOSUCHNICK(Clients[fd]->getPrefix(), splited[1]));
                return;
            }
            else 
            {
                sendMyMsg(fd, ERR_CHANOPRIVSNEEDED(Clients[fd]->getPrefix(), splited[1])); 
                return;
            }
        }
    }
}