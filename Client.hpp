#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>



class Client 
{
    private:
        std::string _nickname;
        std::string _username;
        int _onlineFD;
        bool _pass;
    public:
        Client(std::string, std::string, int fd, struct sockaddr_in address);
        std::string _hostname;
        int ChannelCount;
        bool guest;
        std::string getUsername();
        void setUsername(std::string);
        void setNickname(std::string);
        std::string getNickname();
        bool getPass();
        void setPass(bool);
        int getOnlineFD();
        void setOnlineFD(int fd);
        const std::string getPrefix();
        std::string tmpBuff;
        
       
};

#endif