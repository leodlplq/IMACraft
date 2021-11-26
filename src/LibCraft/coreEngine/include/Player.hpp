//
// Created by leodlplq on 26/11/2021.
//
#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include "../../renderEngine/include/Cube.hpp"

class Player {
public:

    Player() = default;
    Player(const Cube &mesh, const glm::vec3 spawnPos);
    ~Player() = default;

    void moveLeft();
    void moveRight();
    void looseHP();
    void gainHP();
    void jump();
    void slide();

    void Inputs(GLFWwindow* window);

    const glm::vec3 getPosition() const{
        std::cout << _position.x << _position.y << _position.z << std::endl;
        return glm::vec3(_position.x, _position.y, _position.z);
    }

private:
    glm::vec3 _position;
    float _hp;
    Cube _mesh;



};