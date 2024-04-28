
#include "utils.hpp"
#include "Server.hpp"

std::vector<std::string> split(const std::string& s, char delimiter) 
{
    std::vector<std::string> tokens;
    std::string token; 
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) 
    {
        if(token != "" && token != "\n" && token!="\r\n")
            tokens.push_back(trim(token));
    }
    return tokens;
}

std::string trim(const std::string& str) 
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (std::string::npos == first) 
        return "";
    size_t last = str.find_last_not_of(" \t\n\r");

    return str.substr(first, (last - first + 1));
}

void    sendMyMsg(int fd, std::string msg)
{
	 send(fd, msg.c_str(), msg.length(), 0);
}