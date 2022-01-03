//
// Created by leodlplq on 29/12/2021.
//

#include "App.hpp"

void App::renderWinScreen(GLFWwindow *window, double FPS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glClearColor(1.f, 0.f, 1.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// ======== BACKGROUND ===========
    _player.inMenu(true);
    displayGame(FPS);
// ====== SCORE ========
    float textHeightTitle = _textMinecraft.textHeight("SCORE: " + _hud.getScore(), 2.f);
    float textWidthTitle = _textMinecraft.textWidth("SCORE: " + _hud.getScore(), 2.f) + 20;
    float yPosTitle = (static_cast<float>(_height) - textHeightTitle) - 50;
    float xPosTitle = (static_cast<float>(_width) / 2) - (textWidthTitle / 2);
    _textMinecraft.renderText(_textShader, "SCORE: " + _hud.getScore(), xPosTitle, yPosTitle, 2.f, _hud.getFontColor());

    KeyBoardListener(window);
// AFFICHAGE DU SCORE BOARD
    float scaleScore = (2.f*static_cast<float>(_height)) / 1080;
    if (_player.getScore() >= _save.getLowerScore()) {

        _save.SetNewScore(_player.getScore(), _pseudo);

        float yPosB = (static_cast<float>(_height) / 1.5f);



        for (unsigned int i = 0; i < _save.getContent().size(); i++) {
            float textHeight = _textMinecraft.textHeight(_save.getContent()[i], scaleScore);
            if (i != 0) {
                yPosB -= (_textMinecraft.textHeight(_save.getContent()[i - 1], scaleScore));
            }
            float textWidth = _textMinecraft.textWidth(_save.getContent()[i], scaleScore) + 20;
            float yPos = yPosB - (textHeight / 2);
            yPosB = yPos;
            float xPos = (static_cast<float>(_width) / 2) - (textWidth / 2) - 50;
            _textMinecraft.renderText(_textShader, _save.getContent()[i], xPos, yPos, scaleScore, _hud.getFontColor());
        }
    } else {
        float yPosB = (static_cast<float>(_height) / 1.5f);
        for (unsigned int i = 0; i < _save.getContent().size(); i++) {
            float textHeight = _textMinecraft.textHeight(_save.getContent()[i], scaleScore);
            if (i != 0) {
                yPosB -= (_textMinecraft.textHeight(_save.getContent()[i - 1], scaleScore));
            }
            float textWidth = _textMinecraft.textWidth(_save.getContent()[i], scaleScore) + 20;
            float yPos = yPosB - (textHeight / 2);
            yPosB = yPos;
            float xPos = (static_cast<float>(_width) / 2) - (textWidth / 2) - 50;
            _textMinecraft.renderText(_textShader, _save.getContent()[i], xPos, yPos, scaleScore, _hud.getFontColor());
        }
    }


    //BUTTONS
    _buttons[6].render();
    _buttons[7].render();

}