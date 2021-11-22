//
// Created by valentin on 22/11/2021.
//
#include "Camera.hpp"

Camera::Camera(int width , int height, glm::vec3 position):_width(width),_height(height),_position(position){}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);


    view = glm::lookAt(_position, _position + _orientation, _up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)_width/_height,nearPlane,farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader._id,"model"),1,GL_FALSE,glm::value_ptr(_model));
    glUniformMatrix4fv(glGetUniformLocation(shader._id,uniform), 1, GL_FALSE, glm::value_ptr(projection*view));
}

void Camera::Inputs(GLFWwindow *window)
{
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
    {
        _position += _speed * -_orientation;
    }
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
    {
        _rotaxis = glm::vec3(0.0f,1.0f,0.0f);
        _model = glm::rotate(_model,glm::radians(-_rotationspeed), _rotaxis);
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
    {
        _position += _speed * _orientation;

    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
    {
        _rotaxis = glm::vec3(0.0f,1.0f,0.0f);
        _model = glm::rotate(_model,glm::radians(_rotationspeed), _rotaxis);
    }
    if(glfwGetKey(window,GLFW_KEY_R) == GLFW_PRESS)
    {
        _model = glm::mat4(1.0f);
    }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);

        if(_firstClick)
        {
            glfwSetCursorPos(window,(_width/2),(_height/2));
            _firstClick = false;
        }
        double mouseX;
        double mouseY;
        glfwGetCursorPos(window,&mouseX,&mouseY);
        float rotx = _sensitivity * (float)(mouseY - (_height/2))/_height;
        float roty = _sensitivity * (float)(mouseX - (_height/2))/_height;

        //glm::vec3 newOrientation = glm::rotate(_orientation, glm::radians(-rotx),glm::normalize(glm::cross(_orientation,_up)));


        _rotaxis = glm::vec3(1.0f,0.0f,0.0f);
        _model = glm::rotate(_model,glm::radians(rotx), _rotaxis);
        _rotaxis = glm::vec3(0.0f,1.0f,0.0f);
        _model = glm::rotate(_model,glm::radians(roty), _rotaxis);

        glfwSetCursorPos(window,(_width/2),(_height/2));
    }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
        _firstClick = true;
    }

}
