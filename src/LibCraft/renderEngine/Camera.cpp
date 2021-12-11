//
// Created by valentin on 22/11/2021.
//
#include "LibCraft/renderEngine/include/Camera.hpp"

Camera::Camera(const int width , const int height, Player &player):
    _position(player.getPosition()),
    _width((float)width),
    _height((float)height),
    _player(player)
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
    _angleX += degree;
}
void Camera::rotateUp(float degree){
    _angleY += degree;
}


