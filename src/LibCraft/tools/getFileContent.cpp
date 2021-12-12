//
// Created by leodlplq on 22/11/2021.
//

#include "include/getFIleContent.hpp"

std::string get_file_contents(FilePath filePath){
    std::string content;
   // std::cout << filePath << std::endl;
    std::ifstream  fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()){
        std::cerr << "not load" << std::endl;
        return "";
    }

    std::string line = "";

    while(!fileStream.eof()){
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}