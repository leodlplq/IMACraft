//
// Created by valentin on 24/12/2021.
//

#include "LibCraft/coreEngine/include/Collectible.hpp"

void Collectible::Draw(Shader &shader , Camera &camera){
    shader.activate();
    if(_alive && _type ==0) {
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
    if(_alive && _type ==1) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, _position+ glm::vec3(0,0.3,0)); // _position du collectible
        model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1, 0, 0));
        _angle += 2;
        model = glm::rotate(model, glm::radians(_angle), glm::vec3(0, 0, 1));
        model = glm::scale(model,glm::vec3(0.02f, 0.35f, 0.35f));    // it's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(shader._id, "camMatrix"), 1, GL_FALSE,glm::value_ptr(camera.getProjMatrix() * camera.getViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(shader._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
        _model.Draw(shader);
    }

}

void Collectible::Update(Player &player) {
    if (player.getPosition().x > _position.x - 0.4 && player.getPosition().x < _position.x + 0.4) {
        if (player.getPosition().z > _position.z - 0.4 && player.getPosition().z < _position.z + 0.4) {
            if (player.getPosition().y > _position.y - 1 && player.getPosition().y < _position.y + 1) {
                _alive = false;
                _position = glm::vec3(0, 0, 0);
                if (_type == 0) {
                    player.winScore(_value);
                }
                if (_type == 1) {
                    player.gainHP();
                    std::cout << "Hp du bonhomme : " << player.getHp() << std::endl;
                }
            }
        }
    }
}