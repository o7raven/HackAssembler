#include "parser.hpp"

Parser::Parser(const std::string& _instruction){
    //std::cout << "parser created " << std::endl;
    instruction = _instruction;
}
std::string Parser::comp(){
    size_t compStart = instruction.find('=');
    size_t compEnd = instruction.find(';');
    if(compStart != std::string::npos && compEnd == std::string::npos)
        return instruction.substr(compStart + 1, instruction.length());
    else if(compStart != std::string::npos && compEnd != std::string::npos)
        return instruction.substr(compStart + 1, compEnd - compStart - 1);
    else if(compStart == std::string::npos && compEnd != std::string::npos)
        return instruction.substr(0,compEnd);
}
std::string Parser::dest(){
    if(instruction.find('=') != std::string::npos)
        return instruction.substr(0, instruction.find('='));
    else{
        return null;
    }
}
std::string Parser::jump(){
    size_t jumpStart = instruction.find(';');
    if(jumpStart != std::string::npos)
        return instruction.substr(jumpStart + 1, instruction.length());
    return "";
}