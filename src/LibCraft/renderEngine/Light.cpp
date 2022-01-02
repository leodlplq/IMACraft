//
// Created by valen on 29/12/2021.
//
#include "LibCraft/renderEngine/include/Light.hpp"

Light::Light(Shader &shader, Camera &camera, std::vector<glm::vec3> position): _pointLightPositions(position){

    shader.activate();
    glm::mat4 model = glm::mat4(1.0f);
    glUniform3f(glGetUniformLocation(shader._id, "viewPos"),camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
    // directional light
    glUniform3f(glGetUniformLocation(shader._id, "dirLight.direction"),-0.2f, -1.0f, -0.3f);
    glUniform3f(glGetUniformLocation(shader._id, "dirLight.ambient"),0.1f, 0.1f, 0.1f);
    glUniform3f(glGetUniformLocation(shader._id, "dirLight.diffuse"),0.4f, 0.4f, 0.4f);
    for(unsigned int i =0; i<_pointLightPositions.size();i++){
        std::stringstream ss;
        ss << i;
        std::string indice = ss.str();
        //std::cout << ("pointLights[" + indice +"].position").c_str() << std::endl;
        glUniform3f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].position").c_str()), _pointLightPositions[i].x, _pointLightPositions[i].y,_pointLightPositions[i].z);
        glUniform3f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].ambiant").c_str()), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].diffuse").c_str()),  0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].specular").c_str()),   1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].constant").c_str()),1.0f);
        glUniform1f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].linear").c_str()),0.09f);
        glUniform1f(glGetUniformLocation(shader._id, ("pointLights[" + indice +"].quadratic").c_str()),0.032f);
    }
}

void Light::Draw(Shader &shader, Model &modelLampe, Camera &camera) {
    shader.activate();
    for (unsigned int i = 0; i < 3; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, _pointLightPositions[i]);
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));    // it's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(shader._id, "camMatrix"), 1, GL_FALSE,
                           glm::value_ptr(camera.getProjMatrix() * camera.getViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(shader._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
        modelLampe.Draw(shader);
    }
}