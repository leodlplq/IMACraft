//
// Created by leodlplq on 22/11/2021.
//
#pragma once
#include "LibCraft/renderEngine/include/Cube.hpp"
#include "LibCraft/tools/include/filePath.hpp"
#include "LibCraft/tools/include/getFIleContent.hpp"
#include <vector>
#include <fstream>

#include <iostream>

class Map {
private:
    std::vector<Cube> _map;
    glm::vec3 _spawnPoint;

public:

    Map();
    explicit Map(FilePath pathToMap);
    ~Map() = default;

    inline std::vector<Cube> getMap() const {return _map;}
    void generateCubeMap(FilePath pathToMap);
    void display() const;

    inline glm::vec3 getSpawnPoint() const{
        return _spawnPoint;
    }
};