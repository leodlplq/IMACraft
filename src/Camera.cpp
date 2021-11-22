//
// Created by valentin on 22/11/2021.
//
#include "Camera.hpp"

Camera::Camera(int width , int height, glm::vec3 position):_width(width),_height(height),_position(position){}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader)
{
    _projection = glm::perspective(glm::radians(FOVdeg), (float)_width/_height,nearPlane,farPlane);
    if(_tpscam)
    {
        _view = glm::lookAt(_position, glm::vec3(0.0,0.0,0.0) , _up); // CAM TPS
    }
   else
   {
       _view = glm::lookAt(_position, _position + _orientation , _up);
   }
}

void Camera::Inputs(GLFWwindow *window)
{
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        _tpscam = false;
        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);

        if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
        {
            _position += _speed * glm::vec3(_orientation.x,0.0f,_orientation.z);
        }
        if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
        {
            //_rotaxis = glm::vec3(0.0f,1.0f,0.0f);   ROTATION DU MODELE PEUT ETRE UTILE POUR PLAYER.CPP
            //_model = glm::rotate(_model,glm::radians(_rotationspeed), _rotaxis);
            _position += _speed * -glm::normalize(glm::cross(_orientation,_up));
        }
        if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
        {
            _position -= _speed * glm::vec3(_orientation.x,0.0f,_orientation.z);

        }
        if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
        {
            _position += _speed * glm::normalize(glm::cross(_orientation,_up));
        }
        if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            _speed = 0.3f;
        }
        if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        {
            _speed = 0.1f;
        }

        if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            _position += _speed * _up;
        }

        if(glfwGetKey(window,GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            _position -= _speed * _up;
        }

        if(_firstClick == true)
        {
            glfwSetCursorPos(window,(_width/2),(_height/2));
            _position = glm::vec3(0.0f,0.0f,5.0f);
            _orientation = glm::vec3(0.0f,0.0f,-1.0f);
            _firstClick = false;
        }
        double mouseX;
        double mouseY;
        glfwGetCursorPos(window,&mouseX,&mouseY);
        float rotx = _sensitivity * (float)(mouseY - (_height/2))/_height;
        float roty = _sensitivity * (float)(mouseX - (_height/2))/_height;


        glm::vec3 newOrientation = glm::rotate(_orientation,glm::radians(-rotx),glm::normalize(glm::cross(_orientation,_up)));
        if (abs(glm::angle(newOrientation, _up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            _orientation = newOrientation;
        }
        // Rotates the Orientation left and right
        _orientation = glm::rotate(_orientation, glm::radians(-roty), _up);
        glfwSetCursorPos(window,(_width/2),(_height/2));
    }

    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        _tpscam = true;
        if(_firstClick == false)
        {
            _position = glm::vec3(0.0f,0.0f,3.0f);
            _firstClick = true;
        }
        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);

        double mouseX;
        double mouseY;
        glfwGetCursorPos(window,&mouseX,&mouseY);
        float rotx = _sensitivity * (float)(mouseY - (_height/2))/_height;
        float roty = _sensitivity * (float)(mouseX - (_height/2))/_height;
        _rotaxis = glm::vec3(1.0f,0.0f,0.0f);
        _position = glm::rotate(_position,glm::radians(rotx), _rotaxis);
        _rotaxis = glm::vec3(0.0f,1.0f,0.0f);
        _position = glm::rotate(_position,glm::radians(roty), _rotaxis);
        glfwSetCursorPos(window,(_width/2),(_height/2));
    }

}
