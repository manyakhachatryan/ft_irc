#include "../Server.hpp"

void Server::mode_cmd(std::string cmd, int index)
{
    if(isClientFull(Clients[index]->getOnlineFD()) == -1)
    {
        sendMyMsg(Clients[index]->getOnlineFD(),  "You dont have account, the first register or log in\n");
        return;
    }
    
    std::vector<std::string>  splited =  split(cmd, ' '); 
    if (splited.size() < 3 || splited.size() >4)
    {
        sendMyMsg(Clients[index]->getOnlineFD(),  "Incoorect parameters count\n");
        return ;
    } 

    if(Channels.find(splited[1]) == Channels.end())
    {
        sendMyMsg(Clients[index]->getOnlineFD(), ERR_NOSUCHCHANNEL(Clients[index]->getPrefix(),splited[1])); // ete chanel gteal
        return;
    }
    else // ete channel chi gtel
    {
        for(std::vector<int>::iterator it = Channels[splited[1]]->adminIDs.begin(); it != Channels[splited[1]]->adminIDs.end();++it)
        {
            if (index==*it) // ete admina
            {
                if (splited[2][0] == '+')
                {
                    if (splited[2][1] == 'i')
                    {
                        if(splited.size() !=3)
                        {
                            sendMyMsg(Clients[index]->getOnlineFD(),  "Incoorect parameters count\n");
                            return ;
                        }
                        if (!Channels[splited[1]]->mode_i)
                        {
                            Channels[splited[1]]->mode_i = true;
                            sendMyMsg(Clients[index]->getOnlineFD(), "+i mode is set\n");
                            return;
                        }
                        else sendMyMsg(Clients[index]->getOnlineFD(), "Channel already Invite-only\n"); // heto petqa hanel elser-y
                        return ;
                    }
                    if (splited[2][1] == 'k') //MODE #42 +k oulu   
                    {
                        if (splited.size() == 4)
                        {
                            if (!Channels[splited[1]]->mode_k)
                            {
                                Channels[splited[1]]->mode_k = true;
                                Channels[splited[1]]->setPassword(splited[3]);
                                sendMyMsg(Clients[index]->getOnlineFD(), "+k mode is set\n");
                                return;
                            }
                            else 
                            {
                                Channels[splited[1]]->setPassword(splited[3]);
                                sendMyMsg(Clients[index]->getOnlineFD(), "You set a password\n");
                                return;
                            }
                        }  
                        else  sendMyMsg(Clients[index]->getOnlineFD(), "Not enough parameter\n");
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
                                      std::cout<<"++++++++"<<it->first<<std::endl;
                                    std::vector<int>::iterator it2 = std::find(Channels[splited[1]]->clients.begin(), Channels[splited[1]]->clients.end(), it->first);
                                    if(it2!=Channels[splited[1]]->clients.end())
                                    {
                                            std::cout<<"-------"<<it->first<<std::endl;
                                            Channels[splited[1]]->adminIDs.push_back(it->first); // Deleting the element
                                            return;
                                    }
                                }
                            }
                             sendMyMsg(Clients[index]->getOnlineFD(), "Dont exist that user that channel\n");
                             return;
                        }
                        else 
                        {
                            sendMyMsg(Clients[index]->getOnlineFD(), "Not enough parameter\n");
                            return;
                        }
                    }
                    if (splited[2][1] == 't')
                    {
                        if(splited.size() == 3)
                        {
                            if (!Channels[splited[1]]->mode_t)
                            {
                                Channels[splited[1]]->mode_t = true;
                                sendMyMsg(Clients[index]->getOnlineFD(), "+t mode is set\n");
                                return;
                            }
                            else sendMyMsg(Clients[index]->getOnlineFD(), "mode +t is already set\n");
                            return ;
                        }
                        else 
                        {
                            sendMyMsg(Clients[index]->getOnlineFD(), "too much parameter\n");
                            return;
                        }
                    }
                    if (splited[2][1] == 'l') //MODE #c1 +l 10
                    {
                        if (splited.size() == 4)
                        {
                            if (!Channels[splited[1]]->mode_l)
                            {
                                Channels[splited[1]]->mode_l = true;
                                Channels[splited[1]]->ChatLimit = stoi(splited[3]);
                                sendMyMsg(Clients[index]->getOnlineFD(), "+l mode is set\n");
                                return;
                            }
                            else 
                            {
                                sendMyMsg(Clients[index]->getOnlineFD(), "Chat limite chenged\n");
                                Channels[splited[1]]->ChatLimit = stoi(splited[3]);
                                return ;
                            }
                        }
                        else 
                        {
                            sendMyMsg(Clients[index]->getOnlineFD(), ERR_NEEDMOREPARAMS(Clients[index]->getPrefix(),splited[0]));
                            return;
                        } 
                    }
                }


                else if (splited[2][0] == '-')
                {   
                    if (splited[2][1] == 'i')
                    {
                        if(splited.size() !=3)
                        {
                            sendMyMsg(Clients[index]->getOnlineFD(),  "Incoorect parameters count\n");
                            return ;
                        }
                        if (Channels[splited[1]]->mode_i)
                        {
                            Channels[splited[1]]->mode_i = false;
                            sendMyMsg(Clients[index]->getOnlineFD(), "-i mode is set\n");
                            return;
                        }
                        else sendMyMsg(Clients[index]->getOnlineFD(), "Channel is not Invite-only\n"); // heto petqa hanel elser-y
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
                                    sendMyMsg(Clients[index]->getOnlineFD(), "-k mode is set\n");
                                    return;
                                }
                                if (Channels[splited[1]]->getPassword() == "")
                                {
                                    sendMyMsg(Clients[index]->getOnlineFD(), "There is no password that can be removed.\n");
                                    return;
                                }
                            }
                            else
                            {
                                sendMyMsg(Clients[index]->getOnlineFD(), "There is no password that can be removed.\n");
                                return;
                            }
                        }
                        else  sendMyMsg(Clients[index]->getOnlineFD(), "Not enough parametors\n");
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
                                    if(it2!=Channels[splited[1]]->clients.end()){
                                        if (it1 != Channels[splited[1]]->adminIDs.end()) {
                                            Channels[splited[1]]->adminIDs.erase(it1); // Deleting the element
                                            return;
                                        }
                                    }
                                }
                            }
                             sendMyMsg(Clients[index]->getOnlineFD(), "Dont exist that user\n");
                             return;
                        }
                        else 
                        {
                            sendMyMsg(Clients[index]->getOnlineFD(), "Not enough parameter\n");
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
                                sendMyMsg(Clients[index]->getOnlineFD(), "-t mode is set\n");
                                return;
                            }
                            else sendMyMsg(Clients[index]->getOnlineFD(), "mode -t is already set\n");
                            return ;
                        }
                        else 
                        {
                            sendMyMsg(Clients[index]->getOnlineFD(), "too much parameter\n");
                            return;
                        }
                    }
                    if (splited[2][1] == 'l') //MODE #c1 -l 
                    {
                        if (splited.size() == 3)
                        {
                            if (Channels[splited[1]]->mode_l)
                            {
                                Channels[splited[1]]->mode_l = false;
                                sendMyMsg(Clients[index]->getOnlineFD(), "-l mode is set\n");
                                return;
                            }
                            else 
                            {
                                sendMyMsg(Clients[index]->getOnlineFD(), "mode -l is already set\n");
                                return ;
                            }
                        }
                        else 
                        {
                            sendMyMsg(Clients[index]->getOnlineFD(), ERR_NEEDMOREPARAMS(Clients[index]->getPrefix(),splited[0]));
                            return;
                        } 
                    }

                }
                sendMyMsg(Clients[index]->getOnlineFD(), "Unknown command\n"); 
                return; // ete admina returna anum amenaverjum
             }
        }
        sendMyMsg(Clients[index]->getOnlineFD(), ERR_CHANOPRIVSNEEDED(splited[1]));
        return;
    }
} 