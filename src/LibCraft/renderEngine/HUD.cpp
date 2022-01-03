//
// Created by valentin on 26/12/2021.
//

#include "LibCraft/renderEngine/include/HUD.hpp"

void HUD::DrawHUD(Shader &shader, Model hud, Model icon, int score, const Text& text, Shader &textShader){
    shader.activate();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,
                           glm::vec3(0.0f, -0.9f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::rotate(model, glm::radians(-90.f), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1, 0, 0));
    model = glm::scale(model,
                       glm::vec3(0.1f, 0.05f, 0.08f));    // it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(glGetUniformLocation(shader._id, "camMatrix"), 1, GL_FALSE,
                       glm::value_ptr(glm::mat4(1.0f)));
    glUniformMatrix4fv(glGetUniformLocation(shader._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
    hud.Draw(shader);

    DrawOnlyScore(shader,icon,score,text,textShader);
}

//void HUD::DrawGameOver(Shader &shader, Model gameOver){
//    shader.activate();
//    glDepthFunc(GL_LEQUAL);
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f)); // translate it down so it's at the center of the scene
//    model = glm::rotate(model,glm::radians(-90.f),glm::vec3(1,0,0));
//    model = glm::scale(model, glm::vec3(0.03f*0.35, 0.01f*0.35, 0.05f*0.35));	// it's a bit too big for our scene, so scale it down
//    glUniformMatrix4fv(glGetUniformLocation(shader._id,"camMatrix"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
//    glUniformMatrix4fv(glGetUniformLocation(shader._id,"model"),1,GL_FALSE,glm::value_ptr(model));
//    gameOver.Draw(shader);
//    glDepthFunc(GL_LESS);
//}

void HUD::DrawOnlyScore(Shader &shader, Model &icon, int score, Text text, Shader &textShader){

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.9f, 0.76f, 0.0f)); // _position de l'icone de score
    model = glm::rotate(model, glm::radians(-90.f), glm::vec3(0, 1, 0));
    _angle += 1;
    model = glm::rotate(model, glm::radians(_angle), glm::vec3(0, 1, 0));
    model = glm::scale(model,glm::vec3(0.016f, 0.02f, 0.016f));    // it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(glGetUniformLocation(shader._id, "camMatrix"), 1, GL_FALSE,glm::value_ptr(glm::mat4(1.0f)));
    glUniformMatrix4fv(glGetUniformLocation(shader._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
    icon.Draw(shader);

    // DRAW THE ACTUAL SCORE
    std::stringstream ss;
    ss << score;
    std::string scoreTxt = ss.str();
    _score = scoreTxt;
    float textHeight = text.textHeight(scoreTxt, 2.f);
    float textWidth = text.textWidth(scoreTxt, 2.f) + 20;
    float yPos = (static_cast<float>(_height) - textHeight) - 20;
    float xPos = (static_cast<float>(_width)) - (textWidth) - 120;
    text.renderText(textShader, scoreTxt, xPos, yPos , 2.f, _colorHud);
}