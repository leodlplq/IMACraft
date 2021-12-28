//
// Created by valentin on 26/12/2021.
//
#pragma once
#include "../src/LibCraft/renderEngine/include/Model.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../src/LibCraft/renderEngine/include/Shader.hpp"


class HUD: public Model{
public:
    HUD() = default;
    void DrawHUD(Shader &shader, Model hud);
    void DrawGameOver(Shader &shader, Model gameOver);
};



