//
// Created by valen on 29/12/2021.
//
#pragma once
#include "glm/glm.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

class Light{
public:
    Light(Shader &shader, Shader &shader2 ,Camera &camera, Model &modelLampe);
};
