# include "../Server.hpp"

void Server::user_cmd(std::string cmd, int fd) 
{
    std::vector<std::string>  splited =  split(cmd, ' '); 
    if(Clients[fd]->getUsername() != "" )
    {
        sendMyMsg(fd,  ERR_ALREADYREGISTRED(splited[0])); // done
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
    if(Clients[fd]->getUsername() == "" )
    {
        Clients[fd]->setUsername(splited[1]);
    } 
}