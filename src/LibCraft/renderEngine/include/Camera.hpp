//
// Created by valentin on 22/11/2021.
//
#pragma once

#include "LibCraft/coreEngine/include/Player.hpp"
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
    //CONSTRUCTORS
    Camera(int width , int height, Player &player, Map &map);
    ~Camera() =default;
    void Matrix(float FOVdeg, float nearPlane, float farPlane);


    //INPUTS EVENTS
    void scrollCallback(double xOffset, double yOffset); //move front camera
    void rotateLeft(float degree);
    void rotateLeftNoMouse(float degree);
    void rotateUp(float degree);

    void turnLeft();
    void turnRight();

    inline glm::mat4 getProjMatrix() const{ return _projection; }
    glm::mat4 getViewMatrix() const;

    inline bool isCamLocked() const { return _isLocked; }
    inline void invertCamLock() {_isLocked = ! _isLocked; };

//    inline bool isCamFPS() const { return _isFPS; }
    inline void invertCamMode() {_isFPS = !_isFPS; };
    void resetAngle();

    //GETTERS OF THE VECTORS
    inline glm::vec3 getPosition() const { return _position; }
    inline glm::vec3 getOrientation() const { return _orientation; }
    inline glm::vec3 getUpVector() const { return _up; }

    //GETTERS OF USEFUL VALUES
    inline float getSensitivity() const { return _sensitivity; }


    //ANIMATION PART
    inline bool isTurningLeft() const { return _turningLeft; }
    inline void setTurningLeft(bool value) { _turningLeft = value; }

    inline bool isTurningRight() const { return _turningRight; }
    inline void setTurningRight(bool value) { _turningRight = value; }

    inline void setCurrentAngleX(float value){ _angleXCurrent = value; }
    inline float getCurrentAngleX() const { return _angleXCurrent; }

    void restart();

private:

    //ANIMATION PART
    Map _map;
    bool _turningLeft = false;
    bool _turningRight = false;
    float _angleXCurrent = 0;

    //VECTORS OF THE CAMERA
    glm::vec3 _position;
    glm::vec3 _orientation;
    glm::vec3 _up = glm::vec3(0.0f,1.0f,0.0f);

    //MATRIXs OF THE CAMERA
    glm::mat4 _projection = glm::mat4(1.0f);

    Player &_player;
    float _distanceFromCamera = 5.0f;
    float _angleX = 30.f;
    float _angleY = -90.f;
    float _angleYWithoutMouseRotation = -90.f;

    float _width;
    float _height;

    //SENSITIVITY PART
    float _scrollSensitivity = 0.5;
    float _sensitivity = 50.0f;

//    float _rotationspeed = 1.5f;


    //LOCK PART
    bool _isLocked = true;

    //CHOICE OF THE CAM PART
    bool _isFPS = false;

};

