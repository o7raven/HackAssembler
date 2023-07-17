#include "code.hpp"

Code::Code(){
    compTable =
    {
    {"0", "0101010"}, 
    {"1", "0111111"},
    {"-1", "0111010"},
    {"D", "0001100"},
    {"A", "0110000"},
    {"!D", "0001101"},
    {"!A", "0110001"},
    {"-D", "0001111"},
    {"-A", "0110011"},
    {"D+1", "0011111"},
    {"A+1", "0110111"},
    {"D-1", "0001110"},
    {"A-1", "0110010"},
    {"D+A", "0000010"},
    {"D-A", "0010011"},
    {"A-D", "0000111"},
    {"D&A", "0000000"},
    {"D|A", "0010101"},

    {"M", "1110000"},
    {"!M", "1110001"},
    {"-M", "1110011"},
    {"M+1", "1110111"},
    {"M-1", "1110010"},
    {"D+M", "1000010"},
    {"D-M", "1010011"},
    {"M-D", "1000111"},
    {"D&M", "1000000"},
    {"D|M", "1010101"}
    };
    destTable = 
    {
        {"null", "000"},
        {"M", "001"},
        {"D", "010"},
        {"MD", "011"},
        {"A", "100"},
        {"AM", "101"},
        {"AD", "110"},
        {"AMD", "111"}
    };
    jumpTable =
    {
        {"", "000"},
        {"null", "000"},
        {"JGT", "001"},
        {"JEQ", "010"},
        {"JGE", "011"},
        {"JLT", "100"},
        {"JNE", "101"},
        {"JLE", "110"},
        {"JMP", "111"}
    };
}
std::string Code::dest(const std::string& _dest){
    if(exists(destTable, _dest))
        return destTable[_dest];
    std::cerr << "Input invalid; Code::dest:" << _dest << std::endl;
    return _dest;

}
std::string Code::comp(const std::string& _comp){
    if(exists(compTable, _comp))
        return compTable[_comp];
    std::cerr << "Input invalid; Code::comp:"<<_comp << std::endl;
    return _comp;

}
std::string Code::jump(const std::string& _jump){
    if(exists(jumpTable, _jump))
        return jumpTable[_jump];
    std::cerr << "Input invalid; Code::jump:"<<_jump << std::endl;
    return _jump;
}

bool Code::exists(const std::unordered_map<std::string, std::string>& tableType,const std::string& tableValue){
    if(tableType.find(tableValue) == tableType.end())
        return false;
    return true;
}