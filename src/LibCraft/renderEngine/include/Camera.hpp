//
// Created by valentin on 22/11/2021.
//
#pragma once

#include <LibCraft/coreEngine/include/Player.hpp>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "LibCraft/renderEngine/include/Shader.hpp"

class Camera
{
    public:
        glm::vec3 _position;
        glm::vec3 _orientation = glm::vec3(0.0f,0.0f,-1.0f);
        glm::vec3 _up = glm::vec3(0.0f,1.0f,0.0f);

        float _width;
        float _height;

        float _speed = 0.1f;
        float _rotationspeed = 1.5f;
        float _sensitivity = 50.0f;
        glm::vec3 _rotaxis;
        glm::mat4 _model = glm::mat4(1.0f);
        glm::mat4 _view = glm::mat4(1.0f);
        glm::mat4 _projection = glm::mat4(1.0f);


        bool _firstClick = true;
        bool _tpscam = true;


        Camera(int width , int height, Player &player);
        void Matrix(float FOVdeg, float nearPlane, float farPlane);


        //INPUTS EVENTS
        void scrollCallback(double xOffset, double yOffset); //move front camera
        void rotateLeft(float degree);
        void rotateUp(float degree);

        glm::mat4 getModelMatrix() const{
            return _model;
        }
        glm::mat4 getViewMatrix() const{
            glm::vec3 shiftCamera = _player.getOrientation() * _distanceFromCamera;

            glm::mat4 translate = glm::translate(glm::mat4(1.f), -shiftCamera);
            glm::mat4 rotX = glm::rotate(glm::mat4(1.f), glm::radians(_angleX), glm::vec3(1, 0, 0));
            glm::mat4 rotY =  glm::rotate(glm::mat4(1.f), glm::radians(_angleY), glm::vec3(0, 1, 0));
            glm::mat4 lookTo = glm::translate(glm::mat4(1.f), -_player.getPosition());
            glm::mat4 view = glm::mat4(translate * rotX * rotY * lookTo);

            return view;

        }
        glm::mat4 getProjMatrix() const{
            return _projection;
        }




    private:
        Player &_player;
        float _distanceFromCamera = 5.0f;
        float _angleX = 10.f;
        float _angleY = 10.f;

        //SENSITIVITY PART
        float _scrollSensitivity = 0.5;
};

