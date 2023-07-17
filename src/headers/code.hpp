#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

class Code
{
private:
    std::unordered_map<std::string, std::string> compTable;
    std::unordered_map<std::string, std::string> destTable;
    std::unordered_map<std::string, std::string> jumpTable;

    bool exists(const std::unordered_map<std::string, std::string>& tableType,const std::string& tableValue);
public:
    Code();
    std::string dest(const std::string& _dest);
    std::string comp(const std::string& _comp);
    std::string jump(const std::string& _jump);
};