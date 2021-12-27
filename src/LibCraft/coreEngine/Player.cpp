//
// Created by leodlplq on 26/11/2021.
//
#include "include/Player.hpp"

Player::Player(const Cube &mesh, const glm::vec3 &spawnPos):
_position(spawnPos), _facingDirection('N'), _mesh(mesh), _hitbox(mesh, spawnPos), _hp(10)
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
    glm::vec3 displacementRight = _speedSide * glm::normalize(glm::cross(glm::rotate(_orientation, glm::radians(_orientationRot), _up),_up));
    _position += displacementRight;

    glm::vec3 newCorner1 = _hitbox.getCorner1() + displacementRight;
    _hitbox.setCorner1( newCorner1 );
    glm::vec3 newCorner2 = _hitbox.getCorner2() + displacementRight;
    _hitbox.setCorner2( newCorner2 );
}

void Player::moveLeft() {
    glm::vec3 displacementLeft = _speedSide * glm::normalize(glm::cross(glm::rotate(_orientation, glm::radians(_orientationRot), _up),_up));
    _position -= displacementLeft;

    glm::vec3 newCorner1 = _hitbox.getCorner1() - displacementLeft;
    _hitbox.setCorner1( newCorner1 );
    glm::vec3 newCorner2 = _hitbox.getCorner2() - displacementLeft;
    _hitbox.setCorner2( newCorner2 );
}

void Player::moveForward(){

    //PLAYER MOVEMENT
    glm::vec3 displacementForward = _speed * glm::rotate(_orientation, glm::radians(_orientationRot), _up);
    _position += displacementForward;

    //PLAYER'S HITBOX MOVEMENT
    glm::vec3 newCorner1 = _hitbox.getCorner1() + displacementForward;
    _hitbox.setCorner1( newCorner1 );
    glm::vec3 newCorner2 = _hitbox.getCorner2() + displacementForward;
    _hitbox.setCorner2( newCorner2 );
}

void Player::moveBackward(){
    glm::vec3 displacementBackward = _speed * glm::rotate(_orientation, glm::radians(_orientationRot), _up);
    _position -= displacementBackward;

    //PLAYER'S HITBOX MOVEMENT
    glm::vec3 newCorner1 = _hitbox.getCorner1() - displacementBackward;
    _hitbox.setCorner1( newCorner1 );
    glm::vec3 newCorner2 = _hitbox.getCorner2() - displacementBackward;-
    _hitbox.setCorner2( newCorner2 );
}

void Player::render(){
    //JUMP PART
    _velocityY -= _gravity;

    glm::vec3 displacementJump = (_speedJump * _velocityY) * glm::vec3(0.f, 1.f, 0.f);
    _position += displacementJump;

    //PLAYER'S HITBOX PART
    glm::vec3 newCorner1 = _hitbox.getCorner1() + displacementJump;
    _hitbox.setCorner1( newCorner1 );
    glm::vec3 newCorner2 = _hitbox.getCorner2() + displacementJump;
    _hitbox.setCorner2( newCorner2 );


    if(_position.y < 1.f){ //STAYING ON THE GROUND AND NOT FALLING INTO INFINTY

        glm::vec3 newCorner1 = glm::vec3(_hitbox.getCorner1().x, 1.5f, _hitbox.getCorner1().z);
        _hitbox.setCorner1( newCorner1 );
        glm::vec3 newCorner2 = glm::vec3(_hitbox.getCorner2().x, 0.5f, _hitbox.getCorner2().z);
        _hitbox.setCorner2( newCorner2 );

        _position.y = 1.f;
        _velocityY = 0.f;
        _onGround = true;
    }

}

void Player::Inputs(GLFWwindow *window) {





    /*if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){ //Z
        moveForward();
    }*/


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



    if(glfwGetKey(window,GLFW_KEY_Q) == GLFW_PRESS){
        if(distanceToPlayer > 0.0f){
            distanceToPlayer -= 1.f;
        }
    }


}

