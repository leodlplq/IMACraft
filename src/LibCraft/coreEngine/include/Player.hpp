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
    void startJump();
    void slide();

    void render();

    void Inputs(GLFWwindow* window);

    const glm::vec3 getPosition() const{
        return glm::vec3(_position.x, _position.y, _position.z);
    }

private:
    glm::vec3 _position;
    glm::vec3 _orientation = glm::vec3(0.0f,0.0f,1.0f);
    glm::vec3 _up = glm::vec3(0.0f,1.0f,0.0f);
    float _hp;
    Cube _mesh;
    float _speed = 0.1f;
    float _speedJump = 0.01f;

    bool _onGround = true;
    int _placement = 0; //define where I am on the the map (0 : mid, -1 : left, 1 : right)


    float _velocityY = 0.f;
    float _gravity = 0.2f;



};