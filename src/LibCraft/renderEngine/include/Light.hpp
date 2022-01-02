//
// Created by valen on 29/12/2021.
//
#pragma once
#include "glm/glm.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

class Light{
public:
    Light() = default;
    Light(Shader &shader,Camera &camera,std::vector<glm::vec3> position);

    void Draw(Shader &shader, Model &modelLampe, Camera &camera);

private:
    std::vector<glm::vec3>_pointLightPositions;
};
