#include "Errors.hpp"

const std::string RPL_WELCOME(const std::string& name)
{ 
    return std::string("001 " + name + " :Welcome " + name + " to the ft_irc network\n"); 
}

const std::string RPL_JOIN(const std::string& name, const std::string& channelName)
{
    return std::string(":" + name + " JOIN " + channelName+"\r\n");
}

const std::string RPL_PING(const std::string& prefix, const std::string& massage) 
{ 
    return std::string(":" + prefix + " PONG :" + massage + "\n"); 
}

const std::string  RPL_MSG(const std::string& prefix,const std::string& command,const std::string& target,const std::string& massage) 
{   
    return std::string( ":" + prefix + " " + command + " " + target + " :" + massage +"\n");  // done
}

const std::string RPL_QUIT(const std::string& prefix, const std::string& massage)
{
    return std::string(":" + prefix + " QUIT :Quit: " + massage + "\n");
}


const std::string RPL_TOPIC(const std::string& channel, const std::string& topic)
{
    return std::string("332 # " + channel + " :" + topic + "\n");
}

const std::string RPL_NOTOPIC(const std::string& channel)
{
    return std::string( "331 # " + channel + "\n");
}    

const std::string RPL_MODE(const std::string& prefix,const std::string& channel,const std::string& target )
{
    return std::string( ":" + prefix + " MODE " + channel + " " + target+"\n");
}  

const std::string RPL_CHANNELMODEIS(const std::string& prefix,const std::string& channel,const std::string& mode, const std::string& modeParams)
{
    return std::string("324 " + prefix + " " + channel + " " + mode + " " + modeParams + ": is set\n");
}

const std::string RPL_INVITING(const std::string& name, const std::string& nick,const std::string& channel)
{
    return std::string( "341 " + name + " " + nick + " " + channel +"\n");
}

const std::string RPL_KICK(const std::string& prefix, const std::string& channel,const std::string& target)
{
    return std::string(":" + prefix + " KICK " + channel + " " + target + "\n");
}

const std::string ERR_NICKNAMEINUSE(const std::string& command, const std::string& name)
{
    return std::string("433 "  + command + " " + name +" : Nickname is already in use\n");
}

const std::string ERR_NEEDMOREPARAMS(const std::string& prefix,const std::string& command) 
{   
    return std::string("461 " + prefix  + " " + command+ " : Requires more parameters\n");  
}

const std::string ERR_CHANNELISFULL(const std::string& prefix,const std::string& name)
{
    return std::string("471 " +prefix + " " +  name  + " : Cannot join channel (+l)\n");
}

const std::string ERR_PASSWDMISMATCH(const std::string& command)  
{
    return std::string("464  " + command + " : Password incorrect\n");
}

const std::string ERR_CHANOPRIVSNEEDED(const std::string& prefix, const std::string& name)
{
    return std::string("482 " +prefix + " " +  name  + " : You're not channel operator\n");
}

const std::string ERR_CANTKICKADMIN(const std::string& name)
{
    return std::string("002 " + name  + " : You are admin, you cant kick yourself from channel\n");
}

const std::string ERR_UNKNOWNMODE(const std::string& source,const std::string& command, const std::string& msg)
{
    return std::string( "472 " + source + " " + command + " " + msg + "\n");
}

const std::string ERR_INVITEONLYCHAN(const std::string& prefix,const std::string& name)
{
    return std::string(" 473 " + prefix + " " +  name  + " : Cannot join channel (+i)\n");
}

const std::string ERR_ALREADYINTHATCHANEL(const std::string& prefix, const std::string& command)
{
    (void)prefix;
    return std::string("003 "  + command + " : You have already in that chanel\n");
}

const std::string ERR_UNKNOWNCOMMAND(const std::string& prefix, const std::string& command)  
{
    return std::string("421 " + prefix + " " + command + " : Unknown command\n");
}

const std::string ERR_NOSUCHCHANNEL(const std::string& prefix, const std::string& name)
{
    return std::string("403 " + prefix + " " +  name  + " : No such channel\n");
}

const std::string ERR_ALREADYREGISTRED(const std::string& command)  
{
    return std::string("462 "  + command + " : You have already entered the data\n");
}

const std::string ERR_NEEDLESSPARAMS(const std::string& prefix,const std::string& command)  
{ 
    return std::string(prefix + " " + command+ " : Requires less parameters\n"); 
}

const std::string ERR_INCORRECTPASS(const std::string prefix, const std::string& command)
{
    return std::string("004 " + prefix + " " + command + " : Incorrect password\n");
}

const std::string ERR_BADCHANMASK(const std::string& prefix, const std::string& command)
{
    return std::string("476  " + prefix + " " + command + " : Bad Channel Mask\n");
}

const std::string ERR_TOOMANYCHANNELS(const std::string& name)
{
    return std::string("405 " + name  + " : You have joined too many channels\n");
}

const std::string  ERR_NOTEXTTOSEND(const std::string& prefix) 
{   
    return std::string("412 " + prefix  + " : No text to send\n");  
}

const std::string  ERR_CANNOTSENDTOCHAN(const std::string& prefix,const std::string& command) 
{   
    return std::string("404 " + prefix  + " " + command+ " :Cannot send to channel\n");  
}

const std::string ERR_NOSUCHNICK(const std::string& prefix, const std::string& name)
{
    return std::string("401 " + prefix + " " +  name  + " : No such nickname\n");
}

                               
const std::string ERR_NOTONCHANNEL(const std::string& prefix,const std::string& command)
{
    return std::string( "442 " + prefix + " " + command + " : You're not on that channel\n");
}  

const std::string ERR_USERONCHANNEL(const std::string& name, const std::string& nick,const std::string& channel)
{
    return std::string( "443 " + name + " " + nick+ " " + channel + " :is already on channel\n");
}

const std::string ERR_NOTREGISTERED(const std::string& prefix)
{
    return std::string( "451 " + prefix + " : You have not registered\n");
}

// const std::string ERR_KEYSET(const std::string& prefix, const std::string& channel)
// {
//     return std::string("467 " + prefix + " " + channel + " :Channel key already set\n");
// }

// const std::string ERR_BADCHANNELKEY(const std::string& name)
// {
//     return std::string("475 " + name  + " : Cannot join channel (+k)\n");
// }
















                             
                                
                           
   
  








   

                 

