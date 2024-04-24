#include "Errors.hpp"


const std::string ERR_PASSISALREADYSET(const std::string& command)
{
    return std::string("000 "  + command + " : Password is already set\n");
}

const std::string ERR_NICKCOLLISION(const std::string& command)
{
    return std::string("436 "  + command + " : Nickname collision KILL\n");
}



const std::string ERR_NICKNAMEINUSE(const std::string& command, const std::string& name)
{
    return std::string("433 "  + command + " " + name +" : Nickname is already in use\n");
}

const std::string ERR_USERISOFLINE(const std::string& command, const std::string& name)
{
    return std::string("001 "  + command  +" : User " + name + " is ofline\n");
}



const std::string ERR_CHANNELISFULL(const std::string& name)
{
    return std::string("471 <" + name  + ">  : Cannot join channel (+l)\n");
}



const std::string ERR_CHANOPRIVSNEEDED(const std::string& name)
{
    return std::string("482 <" + name  + "> :You're not channel operator\n");
}

const std::string ERR_CANTKICKADMIN(const std::string& name)
{
    return std::string("002 <" + name  + "> : You are admin, you cant kick yourself from channel\n");
}

const std::string ERR_UNKNOWNMODE(const std::string& name)
{
    return std::string("472  <" + name  + "> : is unknown mode char to me\n");
}


const std::string ERR_INVITEONLYCHAN(const std::string& name)
{
    return std::string(" 473  <" + name  + "> :Cannot join channel (+i)\n");
}


// ------------







const std::string ERR_ALREADYINTHATCHANEL(const std::string& prefix, const std::string& command)
{
    (void)prefix;
    return std::string("003 "  + command + " : You have already in that chanel\n");
}




//-------------------------------
const std::string  ERR_UNKNOWNCOMMAND(const std::string& prefix, const std::string& command)  // done
{
    return std::string("421 " + prefix + " " + command + " : Unknown command\n");
}

const std::string ERR_NOSUCHCHANNEL(const std::string& prefix, const std::string& name)
{
    return std::string("403 " + prefix + " " +  name  + " : No such channel\n");
}

const std::string  ERR_NEEDMOREPARAMS(const std::string& prefix,const std::string& command) 
{   
    (void)prefix;
    return std::string("461 " + prefix  + " " + command+ " : Requires more parameters\n");  // done
}

const std::string ERR_PASSWDMISMATCH(const std::string& command)  // done
{
    return std::string("464  " + command + " : Password incorrect\n");
}


const std::string ERR_ALREADYREGISTRED(const std::string& command)  // done
{
    return std::string("462 "  + command + " : You have already entered the data\n");
}


const std::string  ERR_NEEDLESSPARAMS(const std::string& prefix,const std::string& command)  // merna /mi tex chi tpum
{ 
    return std::string(prefix + " " + command+ " : Requires less parameters\n"); 
}


const std::string RPL_WELCOME(const std::string& name)
{ 
    return std::string("001 " + name + " :Welcome " + name + " to the ft_irc network\n"); 
}


const std::string ERR_INCORRECTPASS(const std::string prefix, const std::string& command)
{
    (void)prefix;
    return std::string("004 " + prefix + " " + command + " : Incorrect password\n");
}


const std::string RPL_JOIN(const std::string& name, const std::string& channelName)
{
    return std::string(":" + name + " JOIN " + channelName+"\r\n");
}


const std::string RPL_PING(const std::string& prefix, const std::string& massage) //0.5done
{ 
    return std::string(":" + prefix + " PONG :" + massage + "\n"); 
}


const std::string ERR_BADCHANNELKEY(const std::string& name)
{
    return std::string("475 " + name  + " : Cannot join channel (+k)\n");
}

const std::string ERR_BADCHANMASK(const std::string& prefix, const std::string& command)
{
    return std::string("476  " + prefix + " " + command + " : Bad Channel Mask\n");
}


const std::string ERR_TOOMANYCHANNELS(const std::string& name)
{
    return std::string("405 " + name  + " : You have joined too many channels\n");
}


const std::string  ERR_NOTEXTTOSEND(const std::string& prefix,const std::string& command) 
{   
    (void)command;
    return std::string("412 " + prefix  + " : No text to send\n");  
}

const std::string  ERR_CANNOTSENDTOCHAN(const std::string& prefix,const std::string& command) 
{   
    return std::string("404 " + prefix  + " " + command+ " :Cannot send to channel\n");  // done
}

const std::string  RPL_MSG(const std::string& prefix,const std::string& command,const std::string& target,const std::string& massage) 
{   
    return std::string( ":" + prefix + " " + command + " " + target + " :" + massage +"\n");  // done
}

const std::string ERR_NOSUCHNICK(const std::string& prefix, const std::string& name)
{
    return std::string("401 " + prefix + " " +  name  + " : No such nickname\n");
}

const std::string RPL_QUIT(const std::string& prefix, const std::string& massage)
{
    return std::string(":" + prefix + " QUIT :Quit: " + massage + "\n");
}


                                  