#include "../Server.hpp"

void Server::pass_cmd(std::string cmd, int fd)
{  
    std::vector<std::string>  splited =  split(cmd, ' '); 
    if(Clients[fd]->getPass() == true)
    {
        sendMyMsg(fd,  ERR_ALREADYREGISTRED(splited[0]));
        return ;
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
    if(splited[1] != _password)
    {
        sendMyMsg(fd,  ERR_PASSWDMISMATCH(splited[0])); 
        return ; 
    }
    Clients[fd]->setPass(true);                                                                                            
}
