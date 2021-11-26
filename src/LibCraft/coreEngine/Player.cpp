//
// Created by leodlplq on 26/11/2021.
//
#include "include/Player.hpp"

Player::Player(const Cube &mesh, const glm::vec3 spawnPos):
_mesh(mesh), _position(spawnPos), _hp(10)
{
}

void Player::Inputs(GLFWwindow *window) {
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
    {
        _position += _speed * glm::vec3(_orientation.x,0.0f,_orientation.z);
    }
}
