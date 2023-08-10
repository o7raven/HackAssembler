#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <bitset>
#include <stdio.h>
#include <exception>

#include "headers/parser.hpp"
#include "headers/code.hpp"
#include "headers/dymanicLabelVars.hpp"

bool isAinstruction(const std::string& instruction);
bool isCinstruction(const std::string& instruction);
bool isLabel(const std::string& instruction);
bool isVar(const std::string& instruction);
int toInt(const std::string& str);
void processFile(std::ifstream& assembly,const std::string& hackName);
void cleanFile(std::ifstream& assembly,const std::string& tempFileName);
void checkLabelVars(const std::string& hackName);
void assemble(const std::string& hackName);
std::string removeSpaces(const std::string& memoryBuffer);


int main(int argc, char* argv[]){
    try{
        std::string assemblyName = argv[1];
        std::ifstream assembly(assemblyName);
        if(!assembly.good()){
            std::cout << "File doesn't exist" << std::endl;
            return 1;
        }
        std::string hackName = strtok(argv[1], ".");
        hackName.append(".hack");
        processFile(assembly, hackName);
    }
    catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << "\n";
    }
    catch (...)
    {
        std::cerr << "Unknown exception caught\n";
    }
    return 0;   
}

bool isAinstruction(const std::string& instruction){
    if(instruction.at(0) == '@'){
        for(size_t i = 1; i<instruction.size(); i++){
            if(!std::isdigit(instruction[i]))
                return false;
        }
        return true;
    } 
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
bool isVar(const std::string& instruction){
    if(instruction.at(0) == '@' && !(isAinstruction(instruction)) &&
        dyn_map.label_map.find(instruction.substr(1, instruction.length())) ==
        dyn_map.label_map.end())
            return true;
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
    std::bitset<15> binary(num);
    std::string binaryString = binary.to_string();
    //std::cout << binaryString <<  std::endl;
    return binaryString;
}

void processFile(std::ifstream& assembly, const std::string& hackName){
    cleanFile(assembly,hackName);
    checkLabelVars(hackName);
    assemble(hackName);
}

void cleanFile(std::ifstream& assembly,const std::string& hackName){
    std::string* instructionPtr = new std::string();
    unsigned int instructionPosition = 1;
    
    std::stringstream asssemblyMemoryBuffer;
    while(std::getline(assembly, *instructionPtr)){
        std::string instruction = removeSpaces(*instructionPtr);
        if(instruction == "" || instruction.substr(0,2) == "//")
            continue;
        size_t commentLocation = instruction.find("//");
        if(commentLocation != std::string::npos)
            instruction = instruction.substr(0, commentLocation);
        if(isLabel(instruction)){
            std::string modifiedInstruction = instruction.substr(1,(instruction.length()-2));
            dyn_map.label_map.insert({modifiedInstruction,instructionPosition-1});
            //std::cout << "Label:" << modifiedInstruction << " at " << instructionPosition-1<<std::endl;
            continue;
        }
        asssemblyMemoryBuffer << instruction << "\n";
        //std::cout << instruction << std::endl;
        instructionPosition++;
    }
    delete(instructionPtr);
    unsigned int varStart = 16;
    std::string instruction;
    std::ofstream hackFile(hackName);
    while(std::getline(asssemblyMemoryBuffer, instruction)){
        if(isVar(instruction)){
            std::string modifiedInstruction = instruction.substr(1,instruction.length());
            if(dyn_map.var_map.find(modifiedInstruction) == dyn_map.var_map.end()){
                dyn_map.var_map.insert({modifiedInstruction, varStart});
                //std::cout << modifiedInstruction <<  " at " << varStart << std::endl;
                varStart++;
            }
            //std::cout << instruction << std::endl;
        }
        hackFile << instruction << "\n";
    }
    assembly.close();
    hackFile.close();
}
void checkLabelVars(const std::string& hackName){ 
    std::ifstream hackRead(hackName);
    std::stringstream hackMemoryBuffer;
    hackMemoryBuffer << hackRead.rdbuf();
    std::ofstream hackFile(hackName);
    std::string instruction;
    hackRead.close();
    while(std::getline(hackMemoryBuffer, instruction)){
        if(instruction.at(0) == '@' && !(isAinstruction(instruction))){
            if(dyn_map.label_map.find(instruction.substr(1, instruction.length())) != dyn_map.label_map.end()){
                hackFile << "@" << dyn_map.label_map[instruction.substr(1, instruction.length())] << "\n";
                //std::cout << dyn_map.label_map[instruction. substr(1, instruction.length())] << std::endl;
            }else if(dyn_map.var_map.find(instruction.substr(1, instruction.length())) != dyn_map.var_map.end()){
                hackFile << "@" << dyn_map.var_map[instruction.substr(1, instruction.length())] << "\n";
                //std::cout << dyn_map.var_map[instruction.substr(1, instruction.length())] << std::endl;
            }else{
               std::cout << "checkLabelVars::while::ifVarOrLabel error" << std::endl;
            }
            
            //std::cout << Labels.label_map[label] << std::endl;
            //std::cout  << label << "\n";
            continue;
        }
    hackFile << instruction << "\n";
    }
    hackFile.close();
}
void assemble(const std::string& hackName){
    std::ifstream tempHackRead(hackName);
    std::stringstream hackMemoryBuffer;
    hackMemoryBuffer << tempHackRead.rdbuf();
    tempHackRead.close();

    std::string instruction;
    std::ofstream hackFile(hackName);   
    while(std::getline (hackMemoryBuffer, instruction)){
        if(isAinstruction(instruction)){
            std::string instructionNum = instruction.substr(1, instruction.length());
            std::string binary = toBinary(instructionNum);
            //std::cout << binary << std::endl;
            hackFile << "0" << binary << "\n";
            continue;
        }if(isCinstruction(instruction)){
            Parser parser(instruction);
            Code code;
            
            std::string compBits = code.comp(parser.comp());
            std::string destBits = code.dest(parser.dest());
            std::string jumpBits = code.jump(parser.jump());
            //std::cout << destBits << compBits << jumpBits << std::endl;
            hackFile << "111" << compBits  << destBits << jumpBits << "\n";
            continue;
        }
        //std::cout << instruction << std::endl;
    }
    hackFile.close();
}
std::string removeSpaces(const std::string& input){
    std::string result;
    for(char c : input){
        if(!std::isspace(c)){
            result += c;
        }
    }
    return result;
}