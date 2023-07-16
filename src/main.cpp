#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <bitset>

bool isAinstruction(const std::string& instruction);
std::string toBinary(const std::string& instruction);
bool isCinstruction(const std::string& instruction);
int toInt(const std::string& str);

class Parser
{
private:
    std::string instruction;
public:
    Parser(const std::string& _instruction){
        //std::cout << "parser created " << std::endl;
        instruction = _instruction;
    }
    std::string comp(){
        size_t compStart = instruction.find('=');
        size_t compEnd = instruction.find(';');
        if(compStart != std::string::npos && compEnd == std::string::npos)
            return instruction.substr(compStart + 1, instruction.length());
        else if(compStart != std::string::npos && compEnd != std::string::npos)
            return instruction.substr(compStart + 1, compEnd - compStart - 1);
    }
    std::string dest(){
        return instruction.substr(0, instruction.find('='));
    }
    std::string jump(){
        size_t jumpStart = instruction.find(';');
        if(jumpStart != std::string::npos)
            return instruction.substr(jumpStart + 1, instruction.length());
        return "";
    }
};
class Code
{
public:
    std::string comp(std::string _comp){

    }
    std::string dest(std::string _dest){

    }
    std::string jump(std::string _jump){

    }
};



int main(int argc, char* argv[]){
    std::string instruction;
    std::string assemblyName = argv[1]; 
    std::ifstream assembly(assemblyName);
    if(!assembly.good()){
        std::cout << "File doesn't exist" << std::endl;
        return 1;
    }

    std::string hackName = strtok(argv[1], ".");
    hackName.append(".hack");
    std::ofstream hack(hackName);
    while(std::getline (assembly, instruction)){
        if(instruction == "" || instruction.substr(0,2) == "//")
            continue;
        if(isAinstruction(instruction)){
            std::string instructionNum = instruction.substr(1, instruction.length());
            std::string binary = toBinary(instructionNum);
            hack << "000" << binary << "\n";
            continue;
        }if(isCinstruction(instruction)){
            //std::cout << instruction << std::endl;
            Parser parser(instruction);
            std::string comp = parser.comp();
            std::string dest = parser.dest();
            std::string jump = parser.jump();
        }

        //std::cout << instruction << std::endl;
    }

    
    assembly.close();
    return 0;   
}

bool isAinstruction(const std::string& instruction){
    if(instruction.at(0) == '@')
        return true;
    return false;
}

bool isCinstruction(const std::string& instruction){
    if(instruction.at(0) != '(')
        return true;
    return false;
}

std::string toBinary(const std::string& instruction){
    unsigned int num = toInt(instruction);
    std::bitset<13> binary(num);
    std::string binaryString = binary.to_string();
    //std::cout << binaryString <<  std::endl;
    return binaryString;
}
int toInt(const std::string& str){
    std::istringstream iss(str);
    int result;
    iss >> result;
    //std::cout << result;
    return result;
}