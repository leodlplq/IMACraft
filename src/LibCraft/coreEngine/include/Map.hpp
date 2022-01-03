//
// Created by leodlplq on 22/11/2021.
//
#pragma once
#include "LibCraft/renderEngine/include/Cube.hpp"
#include "LibCraft/coreEngine/include/MapElement.hpp"
#include "LibCraft/tools/include/filePath.hpp"
#include "LibCraft/tools/include/getFIleContent.hpp"
#include "LibCraft/renderEngine/include/Model.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <array>

class Map {

private:
    std::vector<Model> _models;

    std::vector<MapElement> _floor;
    std::vector<MapElement> _secondFloor;
    std::vector<MapElement> _thirdFloor;

    glm::vec3 _spawnPoint;
    float _scale;
    int _size;

public:

    Map() = default;
    Map(const FilePath &pathToMap, std::vector<Model> &models, float scale);
    ~Map() = default;

    inline std::vector<MapElement> getFloor() const {return _floor;}
    inline std::vector<MapElement> getSecondFloor() const {return _secondFloor;}
    inline std::vector<MapElement> getThirdFloor() const {return _thirdFloor;}
    
    void generateCubeMap(const FilePath &pathToMap);

    inline glm::vec3 getSpawnPoint() const{
        return _spawnPoint;
    }
    inline int getSize() const { return _size; }

};