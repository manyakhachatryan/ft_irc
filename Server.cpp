#include "Server.hpp"
#include "utils.hpp"
#include <signal.h>

Server::Server(){}

Server::Server(int portNumber, std::string password)
{
    _password = password;
    _portNumber = portNumber;
}

int Server::getPortNumber(){ return _portNumber;}      
void Server::setPortNumber(int portNumber){ _portNumber = portNumber;}
std::string Server::getPassword() { return _password;}
void Server::setPassword(std::string password){_password = password;}

void Server::createServer()
{
    int opt = TRUE;   
    struct sockaddr_in address;
    int master_socket , addrlen , new_socket  ,  
          max_clients = CLIENTLIMIT , activity, i , valread , sd;   
    int max_sd;   
      
    char buffer[1025];  

    for (i = 0; i < max_clients; i++)   
    {   
        client_socket[i] = 0;   
    }   
         
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)   
    {   
        perror("socket failed");   
        exit(EXIT_FAILURE);   
    }   

   int flags = fcntl(master_socket, F_SETFL, O_NONBLOCK);
    if (flags == -1) {
        perror("fcntl");
        return;
    }
	

    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,  
          sizeof(opt)) < 0 )   
    {   
        perror("setsockopt");   
        exit(EXIT_FAILURE);   
    }   
     

    address.sin_family = AF_INET;   
    address.sin_addr.s_addr = INADDR_ANY;   
    address.sin_port = htons( getPortNumber());   

    if (::bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0 )   
    {   
        perror("bind failed");   
        exit(EXIT_FAILURE);   
    }   
    printf("Listener on port %d \n", getPortNumber());   
         
    if (listen(master_socket, 3) < 0)   
    { 
        perror("listen");   
        exit(EXIT_FAILURE);   
    }   
    addrlen = sizeof(address);   
    puts("Waiting for connections ...");   

    while(TRUE)   
    {   
        FD_ZERO(&readfds);   
        FD_SET(master_socket, &readfds); 
        max_sd = master_socket;   

        for ( i = 0 ; i < max_clients ; i++)   
        {       
            sd = client_socket[i];   
            if(sd > 0){
                FD_SET( sd , &readfds);   
            }   
            if(sd > max_sd)   
                max_sd = sd; 
        }   
    
        activity = select(max_sd + 1, &readfds , NULL , NULL , NULL);   
       
        if (activity < 0)   
        {   
            printf("select error\n");   
        }                  
        if (FD_ISSET(master_socket, &readfds))   
        {   
            if ((new_socket = accept(master_socket,  
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)   
            {   
                perror("accept");   
                exit(EXIT_FAILURE);   
            }   
             
            if(send(new_socket, "You are connected to server\n", 29, 0) != 29 )   
            {   
                perror("send");   
            }   
            puts("Welcome message sent successfully");   
                  
            for (i = 0; i < max_clients; i++)   
            {   
                if( client_socket[i] == 0 )   
                {   
                    client_socket[i] = new_socket;   
                    printf("Adding to list of sockets as %d\n" , i);              
                    break;   
                }   
            }   
            if(i == CLIENTLIMIT){
                send(new_socket, "LIMIT\n", 7, 0);
                close(new_socket);
            }
            
        }   

        for (i = 0; i < max_clients; i++)   
        {   
            sd = client_socket[i];   
            if (FD_ISSET( sd , &readfds))   
            {   
                std::memset(buffer, '\0', sizeof(buffer));
                valread = recv( sd , buffer, 1024, 0);
               
                if (valread  > 0)   
                {   
                    std::map<int, Client*>::iterator it = Clients.find(sd);
                    if (it == Clients.end())
                        Clients.insert(std::make_pair<int, Client*>(sd, new Client("", "", sd, address)));
                    Clients[sd]->tmpBuff+=buffer;     

                    if(buffer[valread-1]=='\n')
                    {
                        if(buffer[0]!='\n')
                            executeCommand(Clients[sd]->tmpBuff, sd);
                        else Clients[sd]->tmpBuff="";
                        buffer[valread] = '\0'; 
                    }
                }   
                else if(valread<=0)
                {    
                    quit_cmd(buffer, sd);
                    buffer[valread] = '\0';                       
                } 
    
                std::cout<<"-----------------------------------------------"<<std::endl;
                std::cout<<"| PASS | GUEST  | OFD | INDEX | CHCOUNT | NICK  "<<std::endl;
                for (std::map<int, Client*>::iterator it = Clients.begin(); it != Clients.end(); ++it)
                {
                    std::cout<<"| "<<it->second->getPass()<<"    | "<<it->second->guest<<"      | "<<it->second->getOnlineFD()<<"   | "<<it->first<< "     | "<<it->second->ChannelCount <<"       | "<<it->second->getNickname() <<std::endl;
                }
                std::cout<<"----------------------------------------------- "<<std::endl;
                std::cout<<"size=============>" <<Clients.size()<<std::endl;
                std::cout<<"ChannelSize=============>" <<Channels.size()<<std::endl;

                for (std::map<std::string, Channel*>::iterator it =  Channels.begin(); it !=  Channels.end(); ++it) 
                {
                     for(std::vector<int>::iterator it1 = Channels[it->first]->adminIDs.begin(); it1 != Channels[it->first]->adminIDs.end();++it1)
                    {
                         std::cout<<*it1<<" ";
                    }
                    std::cout<<" AID ]"<<"" <<"[Max "<<it->second->ChatLimit<<" ]"<<"[PASS "<<it->second->getPassword()<<" ]"<<std::endl;
                    std::cout<<"[mode_k] "<<it->second->mode_k<<" [mode_i] "<<it->second->mode_i<<" [mode_t] "<<it->second->mode_t<<" [mode_l] "<<it->second->mode_l<<std::endl;
                    std::cout<<it->first<<": ";
                        for (unsigned long i = 0; i < it->second->clients.size(); i++)
                        std::cout<<it->second->clients[i]<<" ";
                    std::cout<<std::endl;
                }
            }   
        }
    }   
    close(master_socket);
}


void Server::executeCommand(std::string cmd, int sd)
{
    std::vector<std::string>  splited =  split(cmd, ' '); 
    int s = splited[0].size();
    if(!cmd.compare(0,4, "PASS") && s==4)
        pass_cmd(cmd, sd);
    else if (!cmd.compare(0,4, "NICK") && s==4)
        nick_cmd(cmd, sd); 
    else if (!cmd.compare(0,4, "USER") && s==4)
        user_cmd(cmd, sd);
    else if (!cmd.compare(0,4, "PING") && s==4)
        ping_cmd(cmd, sd);
    else if (!cmd.compare(0,4, "QUIT") && s == 4)
        quit_cmd(cmd, sd);
    else if (!cmd.compare(0,7, "PRIVMSG") && s==7)
        privmsg_cmd(cmd, sd);
    else if (!cmd.compare(0,4, "JOIN") && s==4)
        join_cmd(cmd, sd);
    else if (!cmd.compare(0,3, "WHO") && s==3)
        who_cmd(cmd, sd);
    else if (!cmd.compare(0,4, "KICK") && s==4)
        kick_cmd(cmd, sd);
    else if (!cmd.compare(0,4, "MODE") && s==4)
        mode_cmd(cmd, sd);
    else if (!cmd.compare(0,5, "TOPIC") && s==5)
        topic_cmd(cmd, sd);
    else if (!cmd.compare(0,6, "INVITE") && s==6)
        invite_cmd(cmd, sd);
    else 
        sendMyMsg(sd,  ERR_UNKNOWNCOMMAND(Clients[sd]->getPrefix(), splited[0]));
    if (cmd.compare(0,4, "QUIT"))
    {
         Clients[sd]->tmpBuff="";
    }
    if (cmd.compare(0,4, "QUIT") && s == 4)
    {
         isClientFull(sd); 
    }
}

int Server::isClientFull(int fd)
{
        if(Clients[fd]->getPass()==true && Clients[fd]->getNickname()!="" && Clients[fd]->getUsername()!="")
        {
            if(Clients[fd]->guest){
                sendMyMsg(fd,  RPL_WELCOME(Clients[fd]->getNickname()));
                Clients[fd]->guest = false;
            }
            return 1;
        } 
    return 0;
}


