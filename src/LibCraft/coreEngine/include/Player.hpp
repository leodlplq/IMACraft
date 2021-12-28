//
// Created by leodlplq on 26/11/2021.
//
#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "../../renderEngine/include/Cube.hpp"
#include "Hitbox.hpp"
#include "../src/LibCraft/renderEngine/include/Model.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Map.hpp"


class Player {
public:
    //CONSTRUCTORS & DESTRUCTOR

    Player(Model model, const glm::vec3 &spawnPos, float scale);
    Player() = default;
    inline Player(const Cube &mesh, const glm::vec3 &spawnPos, const Map& map):
        _position(spawnPos), _facingDirection('N'), _mesh(mesh), _hitbox(mesh, spawnPos), _hp(10), _map(map)
    {};
    ~Player() = default;

    void Draw(Shader &shader);


    //player movement.
    void moveLeft();
    void moveRight();
    void moveForward();
    void moveBackward();

    void turnLeft();
    void turnRight();

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
    inline void inverseAbleToMove(){ _ableToMove = !_ableToMove; }

    //GETTERS
    inline glm::vec3 getPosition() const{ return _position; }
    inline glm::vec3 getOrientation() const{ return _orientation; }
    inline char getFacingDirection() const { return _facingDirection; }
    inline Hitbox getHitbox() const { return _hitbox;}
    inline float getScale() const { return  _scale;}
    //SETTERS
    inline float setOrientationRotation(float degree){ return _orientationRot += degree; }
    inline char setFacingOrientation(char dir){return _facingDirection = dir; }

    inline float getDistanceToPlayer() const { return _distanceToPlayer; }
    inline void setDistanceToPlayer(float distance){ _distanceToPlayer = distance; }
    inline void setScale(float scale){_scale = scale;}

private:
    //POSITION & MOVEMENT OF THE PLAYER
    glm::vec3 _position{};
    float _scale{};
    glm::vec3 _orientation = glm::vec3(0.0f,0.0f,1.0f);
    glm::vec3 _up = glm::vec3(0.0f,1.0f,0.0f);
    float _orientationRot = -90.f;

    bool _ableToMove = true;
    //float _placement = 0; //define where I am on the the map (0 : mid, -1 : left, 1 : right)
    /*
     * CAN TAKE 4 DIFFERENTS VALUE:
     * ----- N S W E ------
     * it indicates which direction the player is facing (north, south, west, east)
     * */
    char _facingDirection{};

    //SPEEDS AND VALUE FOR THE MOVEMENT + JUMP OF THE PLAYER
    float _speed = 0.1f;
    float _speedSide = _speed;
    float _speedJump = 0.01f;
    float _velocityY = 0.f;
    float _gravity = 0.2f;
    bool _onGround = true;
    Model _model;
    //HITBOX PART
    Hitbox _hitbox;

    //PLAYER HEALTH
    float _hp;
    //MAP TO GET COLLISION
    Map _map;
    float _distanceToPlayer = 3.f;
};