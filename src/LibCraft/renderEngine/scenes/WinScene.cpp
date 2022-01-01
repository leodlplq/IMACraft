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
    float textHeightTitle = _textMinecraft.textHeight("SCORE: "+_hud.getScore(), 2.f);
    float textWidthTitle = _textMinecraft.textWidth("SCORE: "+_hud.getScore(), 2.f) + 20;
    float yPosTitle = (static_cast<float>(_height) - textHeightTitle) - 50;
    float xPosTitle = (static_cast<float>(_width) / 2) - (textWidthTitle / 2) ;
    _textMinecraft.renderText(_textShader, "SCORE: "+_hud.getScore(), xPosTitle, yPosTitle , 2.f, _hud.getFontColor());

    KeyBoardListener(window);
// AFFICHAGE DU SCORE BOARD
    if(_player.getScore() > _sauv.getLowerScore()){

        _sauv.SetNewScore(_player.getScore(),_pseudo);

        float yPosB = (static_cast<float>(_height)/1.5f);
        for(unsigned int i = 0; i<_sauv.getContent().size();i++) {
            float textHeight = _textMinecraft.textHeight(_sauv.getContent()[i], 2.f);
            if (i != 0) {
                yPosB -= (_textMinecraft.textHeight(_sauv.getContent()[i - 1], 2.f));
            }
            float textWidth = _textMinecraft.textWidth(_sauv.getContent()[i], 2.f) + 20;
            float yPos = yPosB - (textHeight / 2);
            yPosB = yPos;
            float xPos = (static_cast<float>(_width) / 2) - (textWidth / 2) - 50;
            _textMinecraft.renderText(_textShader, _sauv.getContent()[i], xPos, yPos, 2.f, _hud.getFontColor());
        }
        _scoreRegister = true;
    }

    else{
            float yPosB = (static_cast<float>(_height)/1.5f);
            for(unsigned int i = 0; i<_sauv.getContent().size();i++) {
                float textHeight = _textMinecraft.textHeight(_sauv.getContent()[i], 2.f);
                if (i != 0) {
                    yPosB -= (_textMinecraft.textHeight(_sauv.getContent()[i - 1], 2.f));
                }
                float textWidth = _textMinecraft.textWidth(_sauv.getContent()[i], 2.f) + 20;
                float yPos = yPosB - (textHeight / 2);
                yPosB = yPos;
                float xPos = (static_cast<float>(_width) / 2) - (textWidth / 2) - 50;
                _textMinecraft.renderText(_textShader, _sauv.getContent()[i], xPos, yPos, 2.f, _hud.getFontColor());
            }
        }


    //BUTTONS
    _buttons[6].render();
    _buttons[7].render();
}

