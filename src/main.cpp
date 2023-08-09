#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <bitset>

#include "headers/parser.hpp"
#include "headers/code.hpp"
#include "headers/labels.hpp"

bool isAinstruction(const std::string& instruction);
bool isCinstruction(const std::string& instruction);
bool isLabel(const std::string& instruction);
int toInt(const std::string& str);
void processFile(std::ifstream& assembly,const std::string& hackName);
void cleanFile(std::ifstream& assembly,const std::string& hackName);
void checkLabelsVars(const std::string& hackName);

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
    processFile(assembly, hackName);
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

bool isLabel(const std::string& instruction){
    if(instruction.find('(') != std::string::npos){
        return true;
    }
    return false;
}
int toInt(const std::string& str){
    std::istringstream iss(str);
    int result;
    iss >> result;
    //std::cout << result;
    return result;
}
std::string toBinary(const std::string& instruction){
    unsigned int num = toInt(instruction);
    std::bitset<13> binary(num);
    std::string binaryString = binary.to_string();
    //std::cout << binaryString <<  std::endl;
    return binaryString;
}

void processFile(std::ifstream& assembly, const std::string& hackName){
    cleanFile(assembly, hackName);
    checkLabelsVars(hackName);
}

void cleanFile(std::ifstream& assembly, const std::string& hackName){
    std::string instruction;
    std::ofstream hackFile(hackName);
    while(std::getline(assembly, instruction)){
        if(instruction == "" || instruction.substr(0,2) == "//")
            continue;
        size_t commentLocation = instruction.find("//");
        if(commentLocation != std::string::npos)
            instruction = instruction.substr(0, commentLocation); 
        hackFile << instruction << "\n";
    }
    assembly.close();
    hackFile.close();
}
void checkLabelsVars(const std::string& hackName){ 
    unsigned int instructionPosition = 1;
    std::string instruction;
    std::ifstream hackRead(hackName);
    std::ofstream hackWrite(hackName);
    while(std::getline(hackRead, instruction)){
        if(isLabel(instruction)){
            Labels.label_map.insert({instruction,instructionPosition});
            continue;
        }
        hackWrite << instruction << "\n";
        instructionPosition++;
    }
   /*while(std::getline (hackFile, instruction)){
        if(instruction == "" || instruction.substr(0,2) == "//")
            continue;
        if(isAinstruction(instruction)){
            std::string instructionNum = instruction.substr(1, instruction.length());
            std::string binary = toBinary(instructionNum);
            //std::cout << binary << std::endl;
            hack << "000" << binary << "\n";
            continue;
        }if(isCinstruction(instruction)){
            Parser parser(instruction);
            Code code;
            std::string comp = parser.comp();
            std::string dest = parser.dest();
            std::string jump = parser.jump();
            
            std::string compBits = code.comp(comp);
            std::string destBits = code.dest(dest);
            std::string jumpBits = code.jump(jump);
            //std::cout << destBits << compBits << jumpBits << std::endl;
            hack << "111" << compBits  << destBits << jumpBits << "\n";
            continue;
        }

        //std::cout << instruction << std::endl;
    }*/
}