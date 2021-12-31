//
// Created by valen on 30/12/2021.
//

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include "Player.hpp"

class Sauvegarde {

public:
    Sauvegarde() = default;
    Sauvegarde(const char* scorePath, const char* pseudoPath, std::string pathFileCreated);
    inline std::vector<std::string> getContent(){return _fileContent;}
    int getLowerScore();
    void enterGamerz();
    void SetNewScore(int playerScore,std::string newPseudo);

private:
    const char* _pathScore;
    const char* _pathPseudo;
    std::vector<std::string> _score;
    std::vector<std::string> _pseudo;
    std::string _path;
    std::vector<std::string> _fileContent;
    std::vector<int> _scoreInt;
    std::string _gamerz;


};


