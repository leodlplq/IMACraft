//
// Created by leodlplq on 29/12/2021.
//

#include "App.hpp"

void App::renderMainMenu(GLFWwindow *window) {
    glClearColor(0.f, 0.f, 1.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    _textMinecraft.renderText(_textShader, "IMACRAFT",500.0f, 500.0f, 2.f, glm::vec3(0.5, 0.8f, 0.2f));
    _textArial.renderText(_textShader, "This is sample text",25.0f, 25.0f, 0.5f, glm::vec3(0.5, 0.8f, 0.2f));
}

