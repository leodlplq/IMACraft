//
// Created by leodlplq on 29/12/2021.
//

#include "App.hpp"

void App::renderPauseMenu(GLFWwindow *window, double FPS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glClearColor(0.f, 1.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _player.inMenu(true);
    displayGame(FPS);

    float textHeightTitle = _textMinecraft.textHeight("PAUSE", 2.f);
    float textWidthTitle = _textMinecraft.textWidth("PAUSE", 2.f) + 20;
    float yPosTitle = (static_cast<float>(_height) - textHeightTitle) - 50;
    float xPosTitle = (static_cast<float>(_width) / 2) - (textWidthTitle / 2) ;
    _textMinecraft.renderText(_textShader, "PAUSE", xPosTitle, yPosTitle , 2.f, _hud.getFontColor());
    _hud.DrawOnlyScore(_shaderProgram,_models[1], _player.getScore(), _textMinecraft,_textShader);

    _buttons[1].render();
    _buttons[2].render();
    _buttons[8].render();

}

