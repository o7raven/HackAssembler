#pragma once
#include <string>
class Parser
{
private:
    std::string instruction;
public:
    Parser(const std::string& _instruction);
    inline std::string comp();
    inline std::string dest();
    inline std::string jump();
};