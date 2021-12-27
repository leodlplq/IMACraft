//
// Created by valentin on 24/12/2021.
//

#include "LibCraft/coreEngine/include/Collectible.hpp"

void Collectible::Draw(Shader &shader , Camera &camera){
    shader.activate();
    if(_alive) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, _position); // _position du collectible
        model = glm::rotate(model, glm::radians(0.f), glm::vec3(1, 0, 0));
        _angle += 2;
        model = glm::rotate(model, glm::radians(_angle), glm::vec3(0, 1, 0));
        model = glm::scale(model,
                           glm::vec3(0.05f, 0.05f, 0.05f));    // it's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(shader._id, "camMatrix"), 1, GL_FALSE,
                           glm::value_ptr(camera.getProjMatrix() * camera.getViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(shader._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
        _model.Draw(shader);
    }
    else{
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.398f, -0.86f, 0.0f)); // _position du collectible
        model = glm::rotate(model, glm::radians(-90.f), glm::vec3(0, 1, 0));
        model = glm::scale(model,glm::vec3(0.008f, 0.01f, 0.008f));    // it's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(shader._id, "camMatrix"), 1, GL_FALSE,glm::value_ptr(glm::mat4(1.0f)));
        glUniformMatrix4fv(glGetUniformLocation(shader._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
        _model.Draw(shader);
    }
}

void Collectible::Update(Player &player) {
    if (player.getPosition().x > _position.x - 0.1 && player.getPosition().x < _position.x + 0.1) {
        if (player.getPosition().z > _position.z - 0.1 && player.getPosition().z < _position.z + 0.1) {
            _alive = false;
            _position = glm::vec3(0,0,0);
            std::cout << "Collected !" << std::endl;

        }
    }
}