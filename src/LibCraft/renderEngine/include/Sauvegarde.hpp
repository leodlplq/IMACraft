//
// Created by valen on 30/12/2021.
//

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include "LibCraft/coreEngine/include/Player.hpp"

class Sauvegarde {

public:
    Sauvegarde() = default;
    Sauvegarde(std::string scorePath, std::string pseudoPath, std::string pathFileCreated);
    inline std::vector<std::string> getContent() const {return _fileContent;}
    int getLowerScore();
    void SetNewScore(int playerScore,std::string newPseudo);

private:
    std::string _pathScore;
    std::string _pathPseudo;
    std::vector<std::string> _score;
    std::vector<std::string> _pseudo;
    std::string _path;
    std::vector<std::string> _fileContent;
    std::vector<int> _scoreInt;
};


