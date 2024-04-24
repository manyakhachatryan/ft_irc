#ifndef  ERRORS_HPP
# define ERRORS_HPP

#include <iostream>

const std::string  ERR_NEEDMOREPARAMS(const std::string& prefix,const std::string& command);
 
const std::string ERR_PASSWDMISMATCH(const std::string& command);

const std::string ERR_PASSISALREADYSET(const std::string& command);

const std::string ERR_NICKCOLLISION(const std::string& command);

const std::string ERR_ALREADYREGISTRED(const std::string& command);

const std::string ERR_NICKNAMEINUSE(const std::string& command, const std::string& name);

const std::string ERR_USERISOFLINE(const std::string& command, const std::string& name);

const std::string ERR_BADCHANNELKEY(const std::string& name);

const std::string ERR_CHANNELISFULL(const std::string& name);

const std::string ERR_TOOMANYCHANNELS(const std::string& name);

const std::string ERR_CHANOPRIVSNEEDED(const std::string& name);

const std::string ERR_NOSUCHCHANNEL(const std::string& prefix,const std::string& name);

const std::string ERR_CANTKICKADMIN(const std::string& name);

const std::string ERR_UNKNOWNMODE(const std::string& name);


const std::string ERR_INVITEONLYCHAN(const std::string& name);

const std::string ERR_CHANOPRIVSNEEDED(const std::string& name);


////-------
const std::string RPL_WELCOME(const std::string& name);
const std::string ERR_UNKNOWNCOMMAND(const std::string& prefix, const std::string& command);

const std::string  ERR_NEEDLESSPARAMS(const std::string& prefix,const std::string& command) ;

const std::string ERR_ALREADYINTHATCHANEL(const std::string& prefix, const std::string& command);

const std::string ERR_INCORRECTPASS(const std::string prefinc, const std::string& command);
const std::string RPL_JOIN(const std::string& name, const std::string& channelName);
const std::string RPL_PING(const std::string& prefix, const std::string& massage);
const std::string ERR_BADCHANMASK(const std::string& prefix, const std::string& command);
const std::string  ERR_NOTEXTTOSEND(const std::string& prefix,const std::string& command);
const std::string  ERR_CANNOTSENDTOCHAN(const std::string& prefix,const std::string& command) ;
const std::string  RPL_MSG(const std::string& prefix,const std::string& command,const std::string& target,const std::string& massage);

const std::string ERR_NOSUCHNICK(const std::string& prefix, const std::string& name);
const std::string RPL_QUIT(const std::string& prefix, const std::string& massage);
#endif   