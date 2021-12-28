//
// Created by leodlplq on 22/11/2021.
//
#pragma once
#include "LibCraft/renderEngine/include/Cube.hpp"
#include "LibCraft/coreEngine/include/MapElement.hpp"
#include "LibCraft/tools/include/filePath.hpp"
#include "LibCraft/tools/include/getFIleContent.hpp"
#include "LibCraft/renderEngine/include/ModelCube.hpp"
#include <vector>
#include <fstream>

#include <iostream>
#include <array>

class Map {

private:
    //std::vector<Cube> _map;
    std::vector<ModelCube> _models;

    std::vector<MapElement> _floor;
    std::vector<MapElement> _secondFloor;
    glm::vec3 _spawnPoint;

public:

    Map() = default;
    Map(const FilePath &pathToMap, std::vector<ModelCube> &models);
    ~Map() = default;

    //inline std::vector<Cube> getMap() const {return _map;}


    inline std::vector<MapElement> getFloor() const {return _floor;}
    inline std::vector<MapElement> getSecondFloor() const {return _secondFloor;}


    void generateCubeMap(const FilePath &pathToMap);
    void display() const;

    inline glm::vec3 getSpawnPoint() const{
        return _spawnPoint;
    }
};