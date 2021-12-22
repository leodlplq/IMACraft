//
// Created by leodlplq on 26/11/2021.
//
#include "include/Player.hpp"

Player::Player(const Cube &mesh, const glm::vec3 &spawnPos):
_position(spawnPos), _hp(10), _mesh(mesh), _hitbox(mesh, spawnPos)
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

    if(_placement < 1 && _ableToMove == 1){
        if(_placement == 0){
            _ableToMove = false;
        }
        _position += _speedSide * glm::normalize(glm::cross(glm::rotate(_orientation, glm::radians(_orientationRot), _up),_up));
        _placement+= _speedSide;

        //TODO : check for collision

        /*_ableToMove = false;*/



        //std::cout << "placement : " << _placement << " able to move ? : " << _ableToMove <<  std::endl;
    }
}

void Player::moveLeft() {
    /*if(!_movingSide){
        _velocityX = 1.f;
    }*/


    if(_placement > -1 && _ableToMove == 1){
        if(_placement == 0){
            _ableToMove = false;
        }
        _position -= _speedSide * glm::normalize(glm::cross(glm::rotate(_orientation, glm::radians(_orientationRot), _up),_up));
        _placement-= _speedSide;

        /*_ableToMove = false;*/

        //TODO : check for collision


        //std::cout << "placement : " << _placement << " able to move ? : " << _ableToMove <<  std::endl;
    }

}

void Player::moveForward(){
    _position += _speed * glm::rotate(_orientation, glm::radians(_orientationRot), _up);
    //TODO : check for collision
}

void Player::moveBackward(){
    _position -= _speed * glm::rotate(_orientation, glm::radians(_orientationRot), _up);
    //TODO : check for collision
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





    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){ //Z
        moveForward();
    }


    /*if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
        if(_ableToMove){
            std::cout << "going right " << std::endl;
            moveRight();
            _ableToMove = false;

        }
    }*/

    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_RELEASE){
        _ableToMove = true;
    }

    /*if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){ //Q
        if(_ableToMove){
            std::cout << "going left " << std::endl;

            moveLeft();
            _ableToMove = false;

        }
    }*/

    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_RELEASE){ //Q
        _ableToMove = true;
    }

    /*if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS){ //press ; to get this until we use fps cam
        if(_onGround){
            startJump();
        }
    }*/

    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
        moveBackward();
    }



}

