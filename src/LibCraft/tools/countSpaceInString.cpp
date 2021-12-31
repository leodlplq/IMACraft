//
// Created by leodlplq on 30/12/2021.
//
#include "LibCraft/tools/include/countSpaceInString.hpp"

int countSpaceInString(std::string &string){
    int totalSpace = 0;

    for(size_t i = 0; i < string.length(); i++){
        if(string[i] == ' ') totalSpace++;
    }

    return totalSpace;
}