//
// Created by leodlplq on 29/12/2021.
//

#include "App.hpp"

void App::renderWinScreen(GLFWwindow *window) {
    glClearColor(1.f, 0.f, 1.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

