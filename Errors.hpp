#ifndef  ERRORS_HPP
# define ERRORS_HPP

#include <iostream>
const std::string RPL_WELCOME(const std::string& name);
const std::string RPL_JOIN(const std::string& name, const std::string& channelName);
const std::string RPL_PING(const std::string& prefix, const std::string& massage);
const std::string RPL_MSG(const std::string& prefix,const std::string& command,const std::string& target,const std::string& massage);
const std::string RPL_QUIT(const std::string& prefix, const std::string& massage);
const std::string RPL_TOPIC(const std::string& chanel, const std::string& topic);
const std::string RPL_NOTOPIC(const std::string& channel);
const std::string RPL_MODE(const std::string& prefix,const std::string& channel,const std::string& target );
const std::string RPL_CHANNELMODEIS(const std::string& prefix,const std::string& channel,const std::string& mode, const std::string& modeParams);
const std::string RPL_INVITING(const std::string& name, const std::string& nick,const std::string& channel);
const std::string RPL_KICK(const std::string& prefix, const std::string& channel,const std::string& target);const std::string ERR_NOTREGISTERED(const std::string& prefix);

const std::string ERR_NICKNAMEINUSE(const std::string& command, const std::string& name);
const std::string ERR_NEEDMOREPARAMS(const std::string& prefix,const std::string& command);
const std::string ERR_CHANNELISFULL(const std::string& prefix,const std::string& name);
const std::string ERR_PASSWDMISMATCH(const std::string& command);
const std::string ERR_CHANOPRIVSNEEDED(const std::string& prefix, const std::string& name);
const std::string ERR_CANTKICKADMIN(const std::string& name);
const std::string ERR_UNKNOWNMODE(const std::string& source,const std::string& command, const std::string& msg);
const std::string ERR_INVITEONLYCHAN(const std::string& prefix,const std::string& name);
const std::string ERR_ALREADYINTHATCHANEL(const std::string& prefix, const std::string& command);
const std::string ERR_UNKNOWNCOMMAND(const std::string& prefix, const std::string& command);
const std::string ERR_NOSUCHCHANNEL(const std::string& prefix,const std::string& name);
const std::string ERR_ALREADYREGISTRED(const std::string& command);
const std::string ERR_NEEDLESSPARAMS(const std::string& prefix,const std::string& command);
const std::string ERR_INCORRECTPASS(const std::string prefinc, const std::string& command);
const std::string ERR_BADCHANMASK(const std::string& prefix, const std::string& command);
const std::string ERR_TOOMANYCHANNELS(const std::string& name);
const std::string ERR_NOTEXTTOSEND(const std::string& prefix);
const std::string ERR_CANNOTSENDTOCHAN(const std::string& prefix,const std::string& command) ;
const std::string ERR_NOSUCHNICK(const std::string& prefix, const std::string& name);
const std::string ERR_NOTONCHANNEL(const std::string& text,const std::string& command);
const std::string ERR_USERONCHANNEL(const std::string& name, const std::string& nick,const std::string& channel);

// const std::string ERR_BADCHANNELKEY(const std::string& name);

























const std::string ERR_KEYSET(const std::string& prefix, const std::string& channel);




#endif   