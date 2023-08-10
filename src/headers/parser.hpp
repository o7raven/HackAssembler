#pragma once
#include <string>
class Parser
{
private:
    std::string instruction;
    std::string null = "null";
public:
    Parser(const std::string& _instruction);
    std::string comp();
    std::string dest();
    std::string jump();
};
