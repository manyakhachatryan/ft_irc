# include "../Server.hpp"

void Server::ping_cmd(std::string cmd, int index) // done
{
    std::vector<std::string> splited = split(cmd, ' ');
    if(splited.size()==1)
        return;
    std::string msg = "";
    for(unsigned long i = 1; i < splited.size(); i++)
    {
        msg = msg+splited[i]+" ";
    }
    sendMyMsg(Clients[index]->getOnlineFD(),RPL_PING(Clients[index]->getPrefix(), msg));
}