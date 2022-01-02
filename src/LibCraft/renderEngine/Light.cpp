//
// Created by valen on 29/12/2021.
//
#include <utility>

#include "LibCraft/renderEngine/include/Light.hpp"

Light::Light(Shader &shader, Camera &camera, std::vector<glm::vec3> position): _pointLightPositions(std::move(position)){

    shader.activate();
    glm::mat4 model = glm::mat4(1.0f);
    glUniform3f(glGetUniformLocation(shader._id, "viewPos"),camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
    // directional light
    glUniform3f(glGetUniformLocation(shader._id, "dirLight.direction"),-0.2f, -1.0f, -0.3f);
    glUniform3f(glGetUniformLocation(shader._id, "dirLight.ambient"),0.2f, 0.2f, 0.2f);
    glUniform3f(glGetUniformLocation(shader._id, "dirLight.diffuse"),0.6f, 0.6f, 0.6f);
    for(unsigned int i =0; i<_pointLightPositions.size();i++){
        std::stringstream ss;
        ss << i;
        std::string indice = ss.str();
        glUniform3f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].position").c_str()), _pointLightPositions[i].x, _pointLightPositions[i].y,_pointLightPositions[i].z);
        glUniform3f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].ambiant").c_str()), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].diffuse").c_str()), 0.9f, 0.65f, 0.0f);
        glUniform3f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].specular").c_str()),1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].constant").c_str()),1.0f);
        glUniform1f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].linear").c_str()),0.09f);
        glUniform1f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].quadratic").c_str()),0.033f);
    }
}

void Light::Draw(Shader &shader, Model &modelLampe, Camera &camera) {
    shader.activate();
    for (auto & _pointLightPosition : _pointLightPositions) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, _pointLightPosition);
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));    // it's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(shader._id, "camMatrix"), 1, GL_FALSE,
                           glm::value_ptr(camera.getProjMatrix() * camera.getViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(shader._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
        modelLampe.Draw(shader);
    }
}