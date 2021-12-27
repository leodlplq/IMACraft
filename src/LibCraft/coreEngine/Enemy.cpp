//
// Created by valentin on 26/12/2021.
//

#include "LibCraft/coreEngine/include/Enemy.hpp"


void Enemy::DrawEnemy(Player &player, Camera &camera, Shader &shader){
    shader.activate();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,player.getPosition()-glm::vec3(_position.x,_position.y,player.getDistanceToPlayer()+_position.z));
    model = glm::rotate(model,glm::radians(-90.f),glm::vec3(1,0,0));
    model = glm::scale(model, _scale);
    glUniformMatrix4fv(glGetUniformLocation(shader._id,"camMatrix"), 1, GL_FALSE, glm::value_ptr(camera.getProjMatrix()*camera.getViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(shader._id,"model"),1,GL_FALSE,glm::value_ptr(model));
    Draw(shader);
}