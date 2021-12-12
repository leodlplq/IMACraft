//
// Created by leodlplq on 22/11/2021.
//

#include "include/Map.hpp"

Map::Map():_map()
{
}

Map::Map(FilePath pathToMap):
_map()
{
    generateCubeMap(pathToMap);
}
void Map::generateCubeMap(FilePath pathToMap) {
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
            }
        }

        for(int i = 0; i < size; i++){

            for(int j = 0; j < size; j++){
                std::getline(image, line);

                switch (stoi(line)) {
                    case 255:
                        _map.push_back(Cube(i,j,0));
                        break;
                    case 240:
                        _map.push_back(Cube(i,j,0));
                        _map.push_back(Cube(i,j,1));
                        break;
                    case 15:
                        _spawnPoint = glm::vec3(i,1 ,j);
                        _map.push_back(Cube(i,j,0));
                        break;
                    case 90:
                        _map.push_back(Cube(i,j,0));
                        break;

                    /*default:
                        std::cout << "lol y a r" << std::endl;
                        break;*/


                }
                /*float z = stoi(line)/(255/10);
                _map.push_back(Cube(i,j,z));*/

            }

        }
    }


}

void Map::display() const {
    double size = sqrt(_map.size());

    for (double i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {

            //std::cout << _map[j + (i * size)] << " ";
        }
        std::cout << std::endl;
    }
}

