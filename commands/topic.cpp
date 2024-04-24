#include "../Server.hpp"

void Server::topic_cmd(std::string cmd, int fd)
{
    if(!isClientFull(fd))
    {
        sendMyMsg(fd,  "You dont have account, first register\n");
        return; 
    }
    std::vector<std::string>  splited =  split(cmd, ' '); 
    if (splited.size() < 2)
    {
        sendMyMsg(fd, ERR_NEEDMOREPARAMS(Clients[fd]->getPrefix(),splited[0]));
        return ;
    } 
    if(Channels.find(splited[1]) == Channels.end())
    {
        sendMyMsg(fd, ERR_NOSUCHCHANNEL(Clients[fd]->getPrefix(),splited[1])); // ete chanel gteal
        return;
    }
    else 
    {
        if (splited.size() == 2)
        {
            if(Channels[splited[1]]->topic == "")
            {
                sendMyMsg(fd,"The channel dont have topic\n");
                return ;
            }
            else 
            {
                sendMyMsg(fd,Channels[splited[1]]->topic);
                return ;
            }
        } 
        else if (splited.size() >2)
        {
            if(Channels[splited[1]]->mode_t==true)
            {
                std::string txt = "";  
                for(unsigned long i = 2; i < splited.size(); i++)
                {
                    txt = txt+splited[i]+" ";
                }
                Channels[splited[1]]->topic = txt+"\n";
                return;
            }
            else  if(Channels[splited[1]]->mode_t==false)
            {   
                sendMyMsg(fd,"You can't change the topic\n");
                return ;
            }
        }
    }
}