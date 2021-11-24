//
// Created by valentin on 22/11/2021.
//
#pragma once
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
        float _sensitivity = 100.0f;
        glm::vec3 _rotaxis;
        glm::mat4 _model = glm::mat4(1.0f);
        glm::mat4 _view = glm::mat4(1.0f);
        glm::mat4 _projection = glm::mat4(1.0f);


        bool _firstClick = true;
        bool _tpscam = true;


        Camera(int width , int height, glm::vec3 position);
        void Inputs(GLFWwindow* window);
        void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader);

        glm::mat4 getModelMatrix(){
            return _model;
        }
        glm::mat4 getViewMatrix(){
        return _view;
        }
        glm::mat4 getProjMatrix(){
        return _projection;
        }
};
