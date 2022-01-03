//
// Created by leodlplq on 29/12/2021.
//

#include "App.hpp"

void App::renderLooseScreen(GLFWwindow *window, double FPS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glClearColor(0.f, 1.f, 1.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _player.inMenu(true);
    displayGame(FPS);
    _hud.DrawOnlyScore(_shaderProgram,_models[1], _player.getScore(), _textMinecraft,_textShader);

    float textHeightTitle = _textMinecraft.textHeight("WASTED", 3.f);
    float textWidthTitle = _textMinecraft.textWidth("WASTED", 3.f);
    float yPosTitle = (static_cast<float>(_height) /2) - (textHeightTitle /2);
    float xPosTitle = (static_cast<float>(_width) / 2) - (textWidthTitle /2);
    _textMinecraft.renderText(_textShader, "WASTED", xPosTitle, yPosTitle , 3.f, _hud.getFontColor());

    //if(glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS && _player.getHp()==0){
   //     std::cout << "restart" << std::endl;
   //     restart();
   //     setScene(1);
  //  }
    //BUTTONS
    _buttons[4].render();
    _buttons[5].render();
}

