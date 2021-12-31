//
// Created by leodlplq on 29/12/2021.
//

#include "App.hpp"

void App::renderMainMenu(GLFWwindow *window, double FPS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glClearColor(0.f, 0.f, 1.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float textHeightTitle = _textMinecraft.textHeight("IMACRAFT", 2.f);
    float textWidthTitle = _textMinecraft.textWidth("IMACRAFT", 2.f) + 20;
    float yPosTitle = (static_cast<float>(_height) - textHeightTitle) - 50;
    float xPosTitle = (static_cast<float>(_width) / 2) - (textWidthTitle / 2) ;
    _textMinecraft.renderText(_textShader, "IMACRAFT", xPosTitle, yPosTitle , 2.f, glm::vec3(0.5, 0.8f, 0.2f));


    float scaleBaseline = 0.3f;
    std::string baseline = "game made by Leo, Adam and Valentin - IMAC 2";
    float textWidthBaseline = _textMinecraft.textWidth(baseline, scaleBaseline) + (8 * 10 *scaleBaseline);
    float yPosBaseline = 10;
    float xPosBaseline = (static_cast<float>(_width) / 2) - (textWidthBaseline / 2);
    _textArial.renderText(_textShader, baseline ,xPosBaseline, yPosBaseline, scaleBaseline, glm::vec3(0.5, 0.8f, 0.2f));



    _buttons[0].render();


}

