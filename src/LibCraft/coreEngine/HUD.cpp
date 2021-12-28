//
// Created by valentin on 26/12/2021.
//

#include "LibCraft/coreEngine/include/HUD.hpp"

void HUD::DrawHUD(Shader &shader, Model hud){
    shader.activate();
    glDepthFunc(GL_LEQUAL);
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
    glDepthFunc(GL_LESS);
}

void HUD::DrawGameOver(Shader &shader, Model gameOver){
    shader.activate();
    glDepthFunc(GL_LEQUAL);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::rotate(model,glm::radians(-90.f),glm::vec3(1,0,0));
    model = glm::scale(model, glm::vec3(0.03f*0.35, 0.01f*0.35, 0.05f*0.35));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(glGetUniformLocation(shader._id,"camMatrix"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
    glUniformMatrix4fv(glGetUniformLocation(shader._id,"model"),1,GL_FALSE,glm::value_ptr(model));
    gameOver.Draw(shader);
    glDepthFunc(GL_LESS);
}