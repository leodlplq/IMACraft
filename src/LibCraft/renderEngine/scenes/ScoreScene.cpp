//
// Created by Léo on 03/01/2022.
//
#include "App.hpp"

void App::renderScoreScreen(GLFWwindow* window, double FPS){
    glClearColor(0.f, 1.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _player.inMenu(true);
    displayGame(FPS);

    float textHeightTitle = _textMinecraft.textHeight("MEILLEURS SCORES", 2.f);
    float textWidthTitle = _textMinecraft.textWidth("MEILLEURS SCORES", 2.f) + 20;
    float yPosTitle = (static_cast<float>(_height) - textHeightTitle) - 50;
    float xPosTitle = (static_cast<float>(_width) / 2) - (textWidthTitle / 2) ;
    _textMinecraft.renderText(_textShader, "MEILLEURS SCORES", xPosTitle, yPosTitle , 2.f, _hud.getFontColor());


    float scaleScore = (2.f*static_cast<float>(_height)) / 1080;

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


    _buttons[10].render();

}
