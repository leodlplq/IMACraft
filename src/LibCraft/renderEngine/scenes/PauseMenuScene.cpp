//
// Created by leodlplq on 29/12/2021.
//

#include "App.hpp"

void App::renderPauseMenu(GLFWwindow *window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glClearColor(0.f, 1.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

