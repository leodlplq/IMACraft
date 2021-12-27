//
// Created by leodlplq on 26/11/2021.
//
#include "include/Player.hpp"

Player::Player(const Cube &mesh, const glm::vec3 spawnPos):
_position(spawnPos), _hp(10), _mesh(mesh)
{
}

void Player::startJump(){
    if(_onGround){
        _velocityY = 10.f;
        _onGround = false;
    }
    //_position -= glm::vec3(0.f, 1.f, 0.f);
}

void Player::moveRight() {
    if(_placement <= 0){
        _position += _speed * glm::normalize(glm::cross(_orientation,_up));
        _placement++;
    }
}

void Player::moveLeft() {
    if(_placement >= 0){
        _position -= _speed * glm::normalize(glm::cross(_orientation,_up));
        _placement--;
    }
}

void Player::render(){
    //JUMP PART
    _velocityY -= _gravity;
    _position += (_speedJump * _velocityY) * glm::vec3(0.f, 1.f, 0.f);

    if(_position.y < 1.f){ //STAYING ON THE GROUND AND NOT FALLING INTO INFINTY
        _position.y = 1.f;
        _velocityY = 0.f;
        _onGround = true;
    }

}

void Player::Inputs(GLFWwindow *window) {

    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){
        _position += _speed * _orientation;
    }

    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
        moveRight();
    }

    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
        moveLeft();
    }

    if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS){ //press ; to get this until we use fps cam
        if(_onGround){
            startJump();
        }


    }

    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
        _position -= _speed * _orientation;

    }

    if(glfwGetKey(window,GLFW_KEY_Q) == GLFW_PRESS){
        if(distanceToPlayer > 0.0f){
            distanceToPlayer -= 1.f;
        }
    }


}

