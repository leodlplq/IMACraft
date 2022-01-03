//
// Created by valentin on 22/11/2021.
//
#include "LibCraft/renderEngine/include/Camera.hpp"

Camera::Camera(const int width , const int height, Player &player, Map &map):
    _map(map),
    _position(player.getPosition()),
    _orientation(player.getOrientation()),
    _player(player),
    _width(static_cast<float>(width)),
    _height(static_cast<float>(height))
{}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane)
{
    _projection = glm::perspective(glm::radians(FOVdeg), (float)_width/(float)_height,nearPlane,farPlane);


    /*_projection = glm::perspective(glm::radians(FOVdeg), (float)_width/(float)_height,nearPlane,farPlane);
    if(_tpscam)
    {
        _view = glm::lookAt(_position, glm::vec3(0.0,0.0,0.0) , _up); // CAM TPS
    }
    else
    {
        _view = glm::lookAt(_position, _position + _orientation , _up);
    }*/
}


glm::mat4 Camera::getViewMatrix() const{

    glm::mat4 view;

    //std::cout << "angle X : " << _angleX << " | " << " angle Y : " << _angleY << " | " << _angleYWithoutMouseRotation << std::endl;
    if(_isFPS){
        glm::mat4 rotX = glm::rotate(glm::mat4(1.f), glm::radians(_angleX), glm::vec3(1, 0, 0));
        glm::mat4 rotY =  glm::rotate(glm::mat4(1.f), glm::radians(_angleY), glm::vec3(0, 1, 0));

        glm::vec3 whereToLookTo;
        float distanceFromPlayer = 0.52f;
        switch (_player.getFacingDirection()) {
            case 'N':
                whereToLookTo = glm::vec3(-1.f, 0.f,0.f) * distanceFromPlayer;
                break;
            case 'S':
                whereToLookTo = glm::vec3(1.f, 0.f,0.f) * distanceFromPlayer;
                break;
            case 'E':
                whereToLookTo = glm::vec3(0.f, 0.f,-1.f) * distanceFromPlayer;
                break;
            case 'W':
                whereToLookTo = glm::vec3(0.f, 0.f,1.f) * distanceFromPlayer;
                break;
        }


        glm::mat4 lookTo;
        if(_player.isSliding()){
            lookTo = glm::translate(glm::mat4(1.f), -_player.getPosition()  - whereToLookTo);
        } else {
            lookTo = glm::translate(glm::mat4(1.f), -glm::vec3(_player.getPosition().x,_player.getPosition().y + 0.7f, _player.getPosition().z)  - whereToLookTo);
        }
        view = glm::mat4(rotX * rotY* lookTo);
    } else {
        glm::vec3 shiftCamera = _player.getOrientation() * _distanceFromCamera;

        glm::mat4 translate = glm::translate(glm::mat4(1.f), -shiftCamera);
        glm::mat4 rotX = glm::rotate(glm::mat4(1.f), glm::radians(_angleX), glm::vec3(1, 0, 0));
        glm::mat4 rotY =  glm::rotate(glm::mat4(1.f), glm::radians(_angleY), glm::vec3(0, 1, 0));
        glm::mat4 lookTo = glm::translate(glm::mat4(1.f), -_player.getPosition());
        view = glm::mat4(translate * rotX * rotY * lookTo);
    }

    return view;

}

void Camera::scrollCallback(double xOffset, double yOffset){
    _distanceFromCamera += _scrollSensitivity * (float)yOffset;

    //SCROLL LIMIT
    if(_distanceFromCamera < 3){
        _distanceFromCamera = 3;
    }

    if(_distanceFromCamera > 40) {
        _distanceFromCamera = 40;
    }

}

void Camera::rotateLeft(float degree){
    if(_isFPS){
        if(_angleY > _angleYWithoutMouseRotation - 60.f && degree < 0){ //peut pas aller plus a droite

            _angleY += degree;
        }

        if(_angleY < _angleYWithoutMouseRotation + 60.f && degree > 0){
            _angleY += degree;
        }
    } else {
        _angleY += degree;
    }



}
void Camera::rotateUp(float degree){

    if(_isFPS){
        if(_angleX > -65.f && degree < 0){ //peut pas aller plus en haut
            _angleX += degree;
        }

        if(_angleX < 70.f && degree > 0){ //peut pas aller plus en haut
            _angleX += degree;
        }


    } else {
        _angleX += degree;
    }

}

void Camera::resetAngle() {
    if(_isFPS){
        _angleX = 0.f;
    } else {
        _angleX = 30.f;
    }
}

void Camera::rotateLeftNoMouse(float degree) {
    _angleYWithoutMouseRotation += degree;
}

void Camera::turnLeft() {

    int xPlayer = static_cast<int>(round(_player.getPosition().x));
    int yPlayer = static_cast<int>(round(_player.getPosition().z));

    int coord = static_cast<int>((xPlayer * _map.getSize()) + yPlayer);

    if(_map.getFloor()[static_cast<unsigned long>(coord)].isIntersection()){
        setTurningLeft(true);
        rotateLeftNoMouse(-90.f);
    }

}

void Camera::turnRight() {

    int xPlayer = static_cast<int>(round(_player.getPosition().x));
    int yPlayer = static_cast<int>(round(_player.getPosition().z));

    int coord = static_cast<int>((xPlayer * _map.getSize()) + yPlayer);

    if(_map.getFloor()[static_cast<unsigned long>(coord)].isIntersection()){
        setTurningRight(true);
        rotateLeftNoMouse(90.f);
    }
}

void Camera::restart(){
    _distanceFromCamera = 5.0f;
    _angleX = 30.f;
    _angleY = -90.f;
    _angleYWithoutMouseRotation = -90.f;
}


