# include "../Server.hpp"

void Server::join_cmd(std::string cmd, int fd) 
{
    if(!isClientFull(fd))
    {
        sendMyMsg(fd,ERR_NOTREGISTERED(Clients[fd]->getPrefix())); 
        return; 
    }
    std::vector<std::string>  splited =  split(cmd, ' '); 
    if (splited.size() < 2)
    {
        sendMyMsg(fd,   ERR_NEEDMOREPARAMS(Clients[fd]->getPrefix(), splited[0])); 
        return ;
    }
    if (splited.size() >= 4)
    {
        sendMyMsg(fd,   ERR_NEEDLESSPARAMS(Clients[fd]->getPrefix(), splited[0]));
        return ;
    }
    if (splited[1][0] != '#' && splited[1][0] != '&')
    {
        sendMyMsg(fd,  ERR_BADCHANMASK(Clients[fd]->getPrefix(), splited[0]));
        return;
    }
    if(Clients[fd]->ChannelCount >= USERSMAXCHANNELCOUNT)
    {
        sendMyMsg(fd, ERR_TOOMANYCHANNELS(splited[1]));
        return ;
    }
    if(Channels.find(splited[1]) == Channels.end())  
    {  
        Channels.insert(std::pair<std::string, Channel*>(splited[1], new Channel()));
        (Channels[splited[1]]->clients).push_back(fd);
        sendMyMsg(fd,  RPL_JOIN(Clients[fd]->getNickname(), splited[1])); 
        if(Channels[splited[1]]->topic=="")
            sendMyMsg(fd,  RPL_NOTOPIC(splited[1])); 
        else 
            sendMyMsg(fd,  RPL_TOPIC(splited[1], Channels[splited[1]]->topic)); 
        Clients[fd]->ChannelCount++;
        if (splited.size() == 3)
        {
            Channels[splited[1]]->setPassword(splited[2]);
            Channels[splited[1]]->mode_k = true;
        }
        if((Channels[splited[1]]->clients.size() == 1))
        {
            Channels[splited[1]]->adminIDs.push_back(fd);
        }
    }
    else 
    {
        for (unsigned long i = 0; i <  Channels[splited[1]]->clients.size(); i++)
        {
            if(Channels[splited[1]]->clients[i] == fd)
            {
                sendMyMsg(fd, ERR_ALREADYINTHATCHANEL(Clients[fd]->getPrefix(), splited[1])); 
                return;
            }
        }
        if((Channels[splited[1]]->mode_l == true  && Channels[splited[1]]->clients.size() < Channels[splited[1]]->ChatLimit) || Channels[splited[1]]->mode_l == false )//-----------------------looock
        {
            if(Channels[splited[1]]->mode_i == true)
            {
                sendMyMsg(fd, ERR_INVITEONLYCHAN(Clients[fd]->getPrefix(),splited[1]));
                return;
            }
            if (Channels[splited[1]]->mode_k == true)
            {
                if (splited.size() != 3 )
                {
                    sendMyMsg(fd, "You need to insert pass\n");
                    return;
                }
                else if (splited[2] != Channels[splited[1]]->getPassword())
                {
                    sendMyMsg(Clients[fd]->getOnlineFD(), ERR_INCORRECTPASS(Clients[fd]->getPrefix(), splited[1]));
                    return;
                }
            }
            (Channels[splited[1]]->clients).push_back(fd);
            sendMyMsg(fd,  RPL_JOIN(Clients[fd]->getNickname(), splited[1])); 
            if(Channels[splited[1]]->topic=="")
                sendMyMsg(fd,  RPL_NOTOPIC(splited[1])); 
            else 
                sendMyMsg(fd,  RPL_TOPIC(splited[1], Channels[splited[1]]->topic)); 
            Clients[fd]->ChannelCount++;
        } 
        else
        {
            sendMyMsg(fd, ERR_CHANNELISFULL(Clients[fd]->getPrefix(), splited[1]));
        }
    }
}