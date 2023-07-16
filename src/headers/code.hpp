#pragma once
#include <string>
#include <unordered_map>


class Code
{
private:
    static std::unordered_map<std::string, std::string> instructionTable;
public:
    Code();
    std::string comp(std::string _comp){

    }
    std::string dest(std::string _dest){

    }
    std::string jump(std::string _jump){

    }
};

