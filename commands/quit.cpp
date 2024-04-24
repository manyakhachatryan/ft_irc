#include "../Server.hpp"

void Server::quit_cmd(std::string cmd, int fd)
{
    std::vector<std::string>  splited =  split(cmd, ' ');
    std::string msg = "";
    if (splited.size() == 1)
    {   
        msg = "Client exiting from the network";
    }
    else
    {
        for(unsigned long i = 1; i < splited.size(); i++)
        {
            msg = msg + splited[i] + " ";
        }
    }
    for(int i = 0; i < CLIENTLIMIT; i++)
    {
        if(client_socket[i]==fd)
        {
            client_socket[i] = 0;
        }
    }
  
    std::vector<std::string> channelsToDelete;
    std::vector<int> sendMsgFd;
    for (std::map<std::string, Channel*>::iterator it =  Channels.begin(); it !=  Channels.end(); ++it) 
    { 
        for(std::vector<int>::iterator it1 = Channels[it->first]->clients.begin(); it1 != Channels[it->first]->clients.end();)
        {
            if(*it1==fd)
            {
                  it1 = Channels[it->first]->clients.erase(it1);
            }
            else
            {    
                std::vector<int>::iterator it2 = std::find(sendMsgFd.begin(), sendMsgFd.end(), *it1);
                if (it2 == sendMsgFd.end()) 
                {
                    sendMsgFd.push_back(*it1);
                }
                it1++;
            }
        }  
        for(std::vector<int>::iterator it1 = Channels[it->first]->adminIDs.begin(); it1 != Channels[it->first]->adminIDs.end();)
        {
            if(*it1==fd)
            {
                 it1 = Channels[it->first]->adminIDs.erase(it1);
            }
            else
            {
                std::vector<int>::iterator it2 = std::find(sendMsgFd.begin(), sendMsgFd.end(), *it1);
                if (it2 == sendMsgFd.end()) 
                {  
                    sendMsgFd.push_back(*it1);
                }
                it1++;
            }
        }

        if(Channels[it->first]->clients.size()==0)
        {
            channelsToDelete.push_back(it->first);
        }
    }
        for (std::vector<int>::const_iterator it1 = sendMsgFd.begin(); it1 != sendMsgFd.end(); ++it1) 
        {
            sendMyMsg(*it1, RPL_QUIT(Clients[*it1]->getPrefix(), (Clients[fd]->getNickname() + " " +msg))); 
        }

    for (std::vector<std::string>::const_iterator it = channelsToDelete.begin(); it != channelsToDelete.end(); ++it) 
    {
        Channel* channelPtr = Channels[*it];
        Channels.erase(*it);
        delete channelPtr;
    }

    delete  Clients[fd];
    close(fd);
    Clients.erase(fd);
} 


