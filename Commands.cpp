
# include "Server.hpp"

void Server::kick_cmd(std::string cmd, int index)
{
    if(isClientFull(Clients[index]->getOnlineFD()) == -1)
    {
        sendMyMsg(Clients[index]->getOnlineFD(),  "You dont have account, the first register or log in\n");
        return;
    }
    std::vector<std::string>  splited =  split(cmd, ' '); 
    if (splited.size() !=3)
    {
        sendMyMsg(Clients[index]->getOnlineFD(),  "Incorect parameters count\n");
        return ;
    }

    if(Channels.find(splited[1]) == Channels.end())
    {
        sendMyMsg(Clients[index]->getOnlineFD(), ERR_NOSUCHCHANNEL(Clients[index]->getPrefix(),splited[1]));
        return;
    }
    else
    {  
        for(std::vector<int>::iterator it = Channels[splited[1]]->adminIDs.begin(); it != Channels[splited[1]]->adminIDs.end();++it)
        {
            if (index==*it) // ete admina
            {
                for (std::map<int, Client*>::iterator it1 = Clients.begin(); it1 != Clients.end(); ++it1) 
                {
                    if( it1->second->getNickname() == splited[2])
                    {
                        for(std::vector<int>::iterator it2 = Channels[splited[1]]->clients.begin(); it2 != Channels[splited[1]]->clients.end();++it2)
                        {
                            if(it1->first == *it2)
                            {
                                std::cout<<"it1->first"<<it1->first<<std::endl;
                                  std::vector<int>::iterator it3 = std::find(Channels[splited[1]]->adminIDs.begin(), Channels[splited[1]]->adminIDs.end(), it1->first);
                                  if(it3!=Channels[splited[1]]->adminIDs.end())
                                  {
                                        Channels[splited[1]]->adminIDs.erase(it3);
                                  }

                                Channels[splited[1]]->clients.erase(it2);
                                return;
                            }
                        }
                    }
                }   
            }
        }
        sendMyMsg(Clients[index]->getOnlineFD(), ERR_CHANOPRIVSNEEDED(splited[1]));
        return; 
    } 
}








void Server::invite_cmd(std::string cmd, int index)
{
    if(isClientFull(Clients[index]->getOnlineFD()) == -1)
    {
        sendMyMsg(Clients[index]->getOnlineFD(),  "You dont have account, the first register or log in\n");
        return;
    }
    std::vector<std::string>  splited =  split(cmd, ' '); 
    if (splited.size() !=3 )
    {
        sendMyMsg(Clients[index]->getOnlineFD(), ERR_NEEDMOREPARAMS(Clients[index]->getPrefix(),splited[0]));
        return ;
    } 
    if(Channels.find(splited[1]) == Channels.end())
    {
        sendMyMsg(Clients[index]->getOnlineFD(), ERR_NOSUCHCHANNEL(Clients[index]->getPrefix(), splited[1])); // ete chanel chi gtel
        return;
    }
    else 
    {
        for(std::vector<int>::iterator it = Channels[splited[1]]->adminIDs.begin(); it != Channels[splited[1]]->adminIDs.end();++it)
        {
            if (index==*it) // ete admina
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
                                    return;
                                }
                                else
                                {
                                    sendMyMsg(Clients[index]->getOnlineFD(), ERR_CHANNELISFULL(splited[1]));
                                    return;
                                }
                                
                            } 
                            else 
                            {
                                 sendMyMsg(Clients[index]->getOnlineFD(), "Already thia user in chat\n");
                                return;
                            }
                    }
                }
                sendMyMsg(Clients[index]->getOnlineFD(), "Dont exist that user\n");
                return;
            }
            else 
            {
                sendMyMsg(Clients[index]->getOnlineFD(), ERR_CHANOPRIVSNEEDED(splited[1])); 
                return;
            }
        }
    }
}




