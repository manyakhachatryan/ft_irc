#include "../Server.hpp"

void Server::mode_cmd(std::string cmd, int fd)
{
    if(!isClientFull(fd))
    {
        sendMyMsg(fd,  ERR_NOTREGISTERED(Clients[fd]->getPrefix()));
        return; 
    } 
    std::vector<std::string>  splited =  split(cmd, ' '); 
    if (splited.size() < 3)
    {
        sendMyMsg(fd,  ERR_NEEDMOREPARAMS(Clients[fd]->getPrefix(),splited[0])); 
        return ;
    } 
    if (splited.size() > 4)
    {
        sendMyMsg(fd,   ERR_NEEDLESSPARAMS(Clients[fd]->getPrefix(), splited[0]));
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
                std::cout<<"\nete adminga mtnuma stex \n"<<std::endl;
                if (splited[2][0] == '+')
                {
                    if (splited[2][1] == 'i') 
                    {
                        if(splited.size() != 3)
                        {
                            sendMyMsg(fd,   ERR_NEEDLESSPARAMS(Clients[fd]->getPrefix(), splited[0]));
                            return ;
                        }
                        if (!Channels[splited[1]]->mode_i)
                        {
                            Channels[splited[1]]->mode_i = true;
                            sendMyMsg(fd, RPL_CHANNELMODEIS(Clients[fd]->getPrefix(), splited[1], "MODE", splited[2]));
                            return;
                        }
                        else sendMyMsg(fd, "Channel already Invite-only\n");
                        return ;
                    }
                    if (splited[2][1] == 'k')
                    {
                        if (splited.size() == 4)
                        {
                            if (!Channels[splited[1]]->mode_k)
                                Channels[splited[1]]->mode_k = true;
                            Channels[splited[1]]->setPassword(splited[3]);
                            sendMyMsg(fd, RPL_CHANNELMODEIS(Clients[fd]->getPrefix(), splited[1], "MODE", splited[2]));
                            return;
                        }  
                        else
                        {
                            sendMyMsg(fd,  ERR_NEEDMOREPARAMS(Clients[fd]->getPrefix(),splited[0]));
                            return ;
                        }
                    }                    
                    if (splited[2][1] == 'o') 
                    {
                        if (splited.size() == 4)  
                        {
                            for (std::map<int, Client*>::iterator it = Clients.begin(); it != Clients.end(); ++it) 
                            {
                                 if(it->second->getNickname() == splited[3])
                                {
                                    std::vector<int>::iterator it2 = std::find(Channels[splited[1]]->clients.begin(), Channels[splited[1]]->clients.end(), it->first);
                                    std::vector<int>::iterator it3 =std::find(Channels[splited[1]]->adminIDs.begin(), Channels[splited[1]]->adminIDs.end(), fd);
                                    if(it2 != Channels[splited[1]]->clients.end() && it3 != Channels[splited[1]]->adminIDs.end())
                                    {
                                        std::cout<<"in the the the "<<std::endl;
                                        Channels[splited[1]]->adminIDs.push_back(it->first); 
                                        sendMyMsg(fd, RPL_CHANNELMODEIS(Clients[fd]->getPrefix(),splited[1], "MODE", splited[2]));
                                        return;
                                    }
                                    else if(it2 == Channels[splited[1]]->clients.end()) 
                                        sendMyMsg(fd, ERR_NOSUCHNICK(Clients[fd]->getPrefix(),splited[3]));
                                    else if (it3 != Channels[splited[1]]->adminIDs.end())
                                        sendMyMsg(fd, ERR_CHANOPRIVSNEEDED(Clients[fd]->getPrefix(), splited[1]));
                                    return;
                                }
                            }
                            sendMyMsg(fd, ERR_NOSUCHNICK(Clients[fd]->getPrefix(), splited[1]));
                            return;
                        }
                        else 
                        {
                            sendMyMsg(fd,  ERR_NEEDLESSPARAMS(Clients[fd]->getPrefix(),splited[0]));
                            return;
                        }
                    }
                    if (splited[2][1] == 't') 
                    {
                        if(splited.size() == 3)
                        {
                            if (!Channels[splited[1]]->mode_t)
                                Channels[splited[1]]->mode_t = true;
                            sendMyMsg(fd, RPL_CHANNELMODEIS(Clients[fd]->getPrefix(),splited[1], "MODE", splited[2]));
                            return;
                        }
                        else 
                        {
                            sendMyMsg(fd,  ERR_NEEDLESSPARAMS(Clients[fd]->getPrefix(),splited[0]));
                            return;
                        }
                    }
                    if (splited[2][1] == 'l')
                    {
                        if (splited.size() == 4)
                        {
                            if (Channels[splited[1]]->clients.size() > static_cast<unsigned long>(stoi(splited[3])))
                            {
                                sendMyMsg(fd, "Chat users count is more than chat limite\n");
                                return ;
                            }
                            if(static_cast<unsigned long>(stoi(splited[3])) > CLIENTLIMIT )
                            {
                                sendMyMsg(fd, "the limit  more then than Server's client limit\n");
                                return ;
                            }
                            if (!Channels[splited[1]]->mode_l)
                                Channels[splited[1]]->mode_l = true;
                            else 
                                sendMyMsg(fd, "Chat limite chenged\n");
                            Channels[splited[1]]->ChatLimit = stoi(splited[3]);
                            sendMyMsg(fd, RPL_CHANNELMODEIS(Clients[fd]->getPrefix(),splited[1], "MODE", splited[2]));
                            return;
                        }
                        else 
                        {
                            sendMyMsg(fd, ERR_NEEDMOREPARAMS(Clients[fd]->getPrefix(),splited[0]));
                            return;
                        } 
                    }
                }


                else if (splited[2][0] == '-')
                {   
                    if (splited[2][1] == 'i') 
                    {
                        if(splited.size() != 3)
                        {
                            sendMyMsg(fd,   ERR_NEEDLESSPARAMS(Clients[fd]->getPrefix(), splited[0]));
                            return ;
                        }
                        if (Channels[splited[1]]->mode_i)
                        {
                            Channels[splited[1]]->mode_i = false;
                            sendMyMsg(fd, RPL_CHANNELMODEIS(Clients[fd]->getPrefix(),splited[1], "MODE", splited[2]));
                            return;
                        }
                        else sendMyMsg(fd, "Channel is not Invite-only\n");
                        return ;
                    }
                    if (splited[2][1] == 'k')   
                    {
                        if (splited.size() == 3)
                        {
                            if (Channels[splited[1]]->mode_k)
                            {
                                Channels[splited[1]]->mode_k = false;
                                if (Channels[splited[1]]->getPassword() != "")
                                {
                                    Channels[splited[1]]->setPassword("");
                                    sendMyMsg(fd, RPL_CHANNELMODEIS(Clients[fd]->getPrefix(),splited[1], "MODE", splited[2]));
                                    return;
                                }
                                if (Channels[splited[1]]->getPassword() == "")
                                {
                                    sendMyMsg(fd, "There is no password that can be removed.\n");
                                    return;
                                }
                            }
                            else
                            {
                                sendMyMsg(fd, "There is no password that can be removed.\n");
                                return;
                            }
                        }
                        else  sendMyMsg(fd,  ERR_NEEDMOREPARAMS(Clients[fd]->getPrefix(),splited[0]));
                        return ;
                    }

                    if (splited[2][1] == 'o') 
                    {
                        if (splited.size() == 4)  
                        {
                            for (std::map<int, Client*>::iterator it = Clients.begin(); it != Clients.end(); ++it) 
                            {
                                if(it->second->getNickname() == splited[3])
                                {
                                    std::vector<int>::iterator it1 = std::find(Channels[splited[1]]->adminIDs.begin(), Channels[splited[1]]->adminIDs.end(), it->first);
                                    std::vector<int>::iterator it2 = std::find(Channels[splited[1]]->clients.begin(), Channels[splited[1]]->clients.end(), it->first);
                                    if(it2 != Channels[splited[1]]->clients.end())
                                    {
                                        if (it1 != Channels[splited[1]]->adminIDs.end())
                                        {
                                             sendMyMsg(fd, RPL_CHANNELMODEIS(Clients[fd]->getPrefix(),splited[1], "MODE", splited[2]));
                                            Channels[splited[1]]->adminIDs.erase(it1); 
                                            return;
                                        }
                                    }
                                }
                            }
                            sendMyMsg(fd, ERR_NOSUCHNICK(Clients[fd]->getPrefix(), splited[1]));
                            return;
                        }
                        else 
                        {
                            sendMyMsg(fd,  ERR_NEEDLESSPARAMS(Clients[fd]->getPrefix(),splited[0]));
                            return;
                        }
                    }

                    if (splited[2][1] == 't')
                    {
                        if(splited.size() == 3)
                        {
                            if (Channels[splited[1]]->mode_t)
                            {
                                Channels[splited[1]]->mode_t = false;
                                sendMyMsg(fd, RPL_CHANNELMODEIS(Clients[fd]->getPrefix(),splited[1], "MODE", splited[2]));
                                return;
                            }
                            else sendMyMsg(fd, "mode -t is already set\n");
                            return ;
                        }
                        else 
                        {
                            sendMyMsg(fd,  ERR_NEEDLESSPARAMS(Clients[fd]->getPrefix(),splited[0]));
                            return;
                        }
                    }
                    if (splited[2][1] == 'l') 
                    {
                        if (splited.size() == 3)
                        {
                            if (Channels[splited[1]]->mode_l)
                            {
                                Channels[splited[1]]->mode_l = false;
                                sendMyMsg(fd, RPL_CHANNELMODEIS(Clients[fd]->getPrefix(),splited[1], "MODE", splited[2]));
                                return;
                            }
                            else 
                            {
                                sendMyMsg(fd, "mode -l is already set\n");
                                return ;
                            }
                        }
                        else 
                        {
                            sendMyMsg(fd, ERR_NEEDMOREPARAMS(Clients[fd]->getPrefix(),splited[0]));
                            return;
                        } 
                    }
                    else
                         sendMyMsg(fd, ERR_UNKNOWNMODE(Clients[fd]->getPrefix(),splited[2], " is unknown mode\n"));
                        return;
                }
                sendMyMsg(fd,ERR_UNKNOWNMODE(Clients[fd]->getPrefix(),splited[2], " is unknown mode\n"));
                return; 
            }
        }
        sendMyMsg(fd, ERR_CHANOPRIVSNEEDED(Clients[fd]->getPrefix(), splited[1]));
        return;
    }
} 