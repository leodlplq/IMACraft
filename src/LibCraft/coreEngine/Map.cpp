//
// Created by leodlplq on 22/11/2021.
//

#include "include/Map.hpp"


Map::Map(const FilePath &pathToMap, std::vector<Model> &models, float scale):
_models(models),_scale(scale)
{
    generateCubeMap(pathToMap);
}
void Map::generateCubeMap(const FilePath& pathToMap){
    std::string line;
    std::fstream image;
    double size;

    std::cout << pathToMap << std::endl;
    image.open(pathToMap);
    if(image.is_open()){
        for (int i = 0; i < 4; i++) {
            std::getline(image, line);
            if(i == 2){
                size = stoi(line);
                _size = static_cast<int>(size);
            }
        }



        for(int i = 0; i < size; i++){

            for(int j = 0; j < size; j++){
                std::getline(image, line);

                switch (stoi(line)) {
                    case 255: //FLOOR
                        _floor.emplace_back(0,glm::vec3(i,0,j), _models[0], false,_scale,false);
                        _secondFloor.emplace_back(-1,glm::vec3(0),_models[0], false,_scale,false);
                        _thirdFloor.emplace_back(-1,glm::vec3(0),_models[0], false,_scale,false);
                        break;
                    case 240: //WALL
                        _floor.emplace_back(0,glm::vec3(i,0,j), _models[0], false,_scale,false);
                        _secondFloor.emplace_back(1,glm::vec3(i,1,j), _models[1], false,_scale,false);
                        _thirdFloor.emplace_back(-1,glm::vec3(0),_models[0], false,_scale,false);
//
                        break;
                    case 15: //SPAWN POINT
                        _floor.emplace_back(3,glm::vec3(i,0,j), _models[3], false,_scale,false);
                        _secondFloor.emplace_back(-1,glm::vec3(0), _models[0], false,_scale,false);
                        _thirdFloor.emplace_back(-1,glm::vec3(0),_models[0], false,_scale,false);
                        _spawnPoint = glm::vec3(i,1 ,j);
//
                        break;
                    case 90: //INTERSECTION
                        _floor.emplace_back(2,glm::vec3(i,0,j), _models[2], true,_scale,false);
                        _secondFloor.emplace_back(-1,glm::vec3(0), _models[0], true,_scale,false);
                        _thirdFloor.emplace_back(-1,glm::vec3(0),_models[0], true,_scale,false);
//
                        break;
                    case 0: //VOID
                        _floor.emplace_back(-1,glm::vec3(0), _models[0], false,_scale,false);
                        _secondFloor.emplace_back(-1,glm::vec3(0), _models[0], false,_scale,false);
                        _thirdFloor.emplace_back(-1,glm::vec3(0),_models[0], false,_scale,false);

                        break;
                    case 180: //OBSTACLE DOWN
                        _floor.emplace_back(-1,glm::vec3(0), _models[0], false,_scale,false);
                        _secondFloor.emplace_back(3,glm::vec3(i,1,j), _models[3], false,_scale,false);
                        _thirdFloor.emplace_back(-1,glm::vec3(0),_models[0], false,_scale,false);
                        break;
                    case 120: //OBSTACLE UP
                        _floor.emplace_back(0,glm::vec3(i,0,j), _models[0], false,_scale,false);
                        _secondFloor.emplace_back(-1,glm::vec3(0), _models[0], false,_scale,false);
                        _thirdFloor.emplace_back(3,glm::vec3(i,2,j),_models[3], false,_scale,false);
                        break;
                    case 30: //FINISH LINE
                        _floor.emplace_back(2,glm::vec3(i,0,j), _models[2], false,_scale, true);
                        _secondFloor.emplace_back(-1,glm::vec3(0), _models[0], false,_scale, true);
                        _thirdFloor.emplace_back(-1,glm::vec3(i,2,j),_models[0], false,_scale, true);
                        break;
                    default:
                        std::cout << "lol y a r" << std::endl;
                        break;


                }


            }

        }
    }


}

void Map::display() const {
    double size = sqrt(static_cast<double>(_floor.size()));

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {

            //std::cout << _map[j + (i * size)] << " ";
        }
        //std::cout << std::endl;
    }
}

