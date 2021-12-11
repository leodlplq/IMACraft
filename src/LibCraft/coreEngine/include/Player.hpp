//
// Created by leodlplq on 26/11/2021.
//
#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "../../renderEngine/include/Cube.hpp"

class Player {
public:

    Player() = default;
    Player(const Cube &mesh, glm::vec3 spawnPos);
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
        return _position;
    }

    const glm::vec3 getOrientation() const{
        return _orientation;
    }

private:
    glm::vec3 _position;
    glm::vec3 _orientation = glm::vec3(0.0f,0.0f,1.0f);
    float _orientationRot = -90.f;
    glm::vec3 _up = glm::vec3(0.0f,1.0f,0.0f);
    float _hp;
    Cube _mesh;
    float _speed = 0.05f;
    float _speedJump = 0.01f;

    bool _onGround = true;
    float _placement = 0; //define where I am on the the map (0 : mid, -1 : left, 1 : right)


    float _velocityY = 0.f;
    float _gravity = 0.2f;



};