//
// Created by valen on 30/12/2021.
//

#include <sstream>
#include <utility>
#include "LibCraft/renderEngine/include/Sauvegarde.hpp"

Sauvegarde::Sauvegarde(std::string scorePath, std::string pseudoPath, std::string pathFileCreated):
_pathScore(std::move(scorePath)),_pathPseudo(std::move(pseudoPath)),_path(std::move(pathFileCreated))
{
    // Va chercher les valeurs des meilleurs scores et les stocks dans des tableaux
    std::ifstream file(_pathScore.c_str());
    std::string str;
    while (std::getline(file, str))
    {
        _score.push_back(str);
        _scoreInt.push_back(std::stoi(str));
    }
    // Va chercher les pseudos des meilleurs joueurs et les stocks dans des tableaux
    std::ifstream file2(_pathPseudo.c_str());
    std::string str2;
    while (std::getline(file2, str2))
    {
        _pseudo.push_back(str2);
    }
//    // Construit un nouveaux fichier à partir des deux autres pour l'affichage du Score Board
//    std::ofstream o(_path.c_str());
//    o << "SCORE BOARD" << std::endl;
//    for(unsigned int i =0; i<_pseudo.size();i++){
//        o << _pseudo[i] << " ------- "<< _score[i] << std::endl;
//    }
    std::ifstream file3(_path.c_str());
    std::string str3;
    while (std::getline(file3, str3))
    {
        _fileContent.push_back(str3);
    }
}


int Sauvegarde::getLowerScore(){
    int min = _scoreInt[0];
    for(unsigned int i = 0;i<_scoreInt.size();i++){
        if (min >= _scoreInt[i])
            min = _scoreInt[i];
    }
    return min;
}

void Sauvegarde::SetNewScore(int playerScore,std::string newPseudo) {
    std::stringstream ss;
    ss << playerScore;
    std::string scoreTxt = ss.str();
    std::stringstream pp;
    pp << newPseudo;
    std::string pseudo = pp.str();

    if(playerScore >= _scoreInt[0]){
        _score[0] = scoreTxt;
        _pseudo[0] = pseudo;

    }
    if(playerScore >= _scoreInt[1] && playerScore < _scoreInt[0]){

//        std::string sco = _score[1];
//        std::string pse = _pseudo[1];
//        _score[2] = sco;
//        _pseudo[2] = pse;

        _score[1] = scoreTxt;
        _pseudo[1] = pseudo;
    }
    if(playerScore >= _scoreInt[2] && playerScore < _scoreInt[1]){
        _score[2] = scoreTxt;
        _pseudo[2] = pseudo;

    }

    std::ofstream o(_path.c_str());
    o << "SCORE BOARD" << std::endl;
    for(unsigned int i =0; i<_pseudo.size();i++){
        o << _pseudo[i] << " ------- "<< _score[i] << std::endl;
    }
    o.close();
    std::ofstream s(_pathScore.c_str());
    for(unsigned int i =0; i<_score.size();i++){
        s <<_score[i] << std::endl;
    }
    s.close();
    std::ofstream p(_pathPseudo.c_str());
    for(unsigned int i =0; i<_pseudo.size();i++){
        p <<_pseudo[i] << std::endl;
    }
    p.close();

    std::ifstream file3(_path.c_str());
    std::string str3;
    _fileContent.clear();
    while (std::getline(file3, str3))
    {
        _fileContent.push_back(str3);
    }

}
