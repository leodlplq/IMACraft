//
// Created by valen on 29/12/2021.
//
#include "LibCraft/renderEngine/include/Light.hpp"

Light::Light(Shader &shader,Shader &shader2, Camera &camera, Model &modelLampe) {
    shader.activate();
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 pointLightPositions[] = {glm::vec3(120.0f, 1.5f, 12.0f),
                                       glm::vec3(120.0f, 1.5f, 8.0f)};

    glUniform3f(glGetUniformLocation(shader._id, "viewPos"),camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
    // directional light
    glUniform3f(glGetUniformLocation(shader._id, "dirLight.direction"),-0.2f, -1.0f, -0.3f);
    glUniform3f(glGetUniformLocation(shader._id, "dirLight.ambient"),0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(shader._id, "dirLight.diffuse"),0.4f, 0.4f, 0.4f);
    glUniform3f(glGetUniformLocation(shader._id, "dirLight.diffuse"),0.5f, 0.5f, 0.5f);
    // point light 1
    glUniform3f(glGetUniformLocation(shader._id, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y,pointLightPositions[0].z);
    glUniform3f(glGetUniformLocation(shader._id, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(shader._id, "pointLights[0].diffuse"),  0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(shader._id, "pointLights[0].specular"),   1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(shader._id, "pointLights[0].constant"),1.0f);
    glUniform1f(glGetUniformLocation(shader._id, "pointLights[0].linear"),0.09f);
    glUniform1f(glGetUniformLocation(shader._id, "pointLights[0].quadratic"),0.032f);
    // point light 2
    glUniform3f(glGetUniformLocation(shader._id, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y,pointLightPositions[1].z);
    glUniform3f(glGetUniformLocation(shader._id, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(shader._id, "pointLights[1].diffuse"),  0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(shader._id, "pointLights[1].specular"),   1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(shader._id, "pointLights[1].constant"),1.0f);
    glUniform1f(glGetUniformLocation(shader._id, "pointLights[1].linear"),0.09f);
    glUniform1f(glGetUniformLocation(shader._id, "pointLights[1].quadratic"),0.032f);

    shader2.activate();
    for(unsigned int i =0; i<2;i++){
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[i]);
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));    // it's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(shader2._id, "camMatrix"), 1, GL_FALSE,glm::value_ptr(camera.getProjMatrix() * camera.getViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(shader2._id, "model"), 1, GL_FALSE, glm::value_ptr(model));
        modelLampe.Draw(shader2);
    }


}
