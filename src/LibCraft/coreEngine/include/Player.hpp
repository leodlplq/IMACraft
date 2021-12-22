//
// Created by leodlplq on 26/11/2021.
//
#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "../../renderEngine/include/Cube.hpp"
#include "Hitbox.hpp"

class Player {
public:
    //CONSTRUCTORS & DESTRUCTOR
    Player() = default;
    Player(const Cube &mesh, const glm::vec3 &spawnPos);
    ~Player() = default;


    //player movement.
    void moveLeft();
    void moveRight();
    void moveForward();
    void moveBackward();

    void startJump();
    void slide();

    //HP PLAYER
    void looseHP();
    void gainHP();


    void render();

    void Inputs(GLFWwindow* window);

    inline void display() const{
        std::cout << "player position is : " << " x : " << _position.x  <<" y : " << _position.y << " z : " << _position.z << std::endl;
    }

    inline void inverseAbleToMove(){
        _ableToMove = !_ableToMove;
    }

    glm::vec3 getPosition() const{
        return _position;
    }

    glm::vec3 getOrientation() const{
        return _orientation;
    }

    Hitbox getHitbox() const {
        return _hitbox;
    }

private:
    glm::vec3 _position;
    glm::vec3 _orientation = glm::vec3(0.0f,0.0f,1.0f);
    float _orientationRot = -90.f;
    glm::vec3 _up = glm::vec3(0.0f,1.0f,0.0f);
    float _hp;
    Cube _mesh;
    float _speed = 0.05f;
    float _speedSide = 1.f;
    float _speedJump = 0.01f;

    bool _ableToMove = true;
    float _placement = 0; //define where I am on the the map (0 : mid, -1 : left, 1 : right)

    bool _onGround = true;
    float _velocityY = 0.f;
    float _gravity = 0.2f;

    Hitbox _hitbox;



};