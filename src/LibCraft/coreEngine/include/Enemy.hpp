//
// Created by valentin on 26/12/2021.
//
#pragma once
#include "../src/LibCraft/renderEngine/include/Model.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../src/LibCraft/renderEngine/include/Shader.hpp"
#include "../src/LibCraft/renderEngine/include/Camera.hpp"


class Enemy: public Model{

private:
    glm::vec3 _position = glm::vec3(0,0,0);
    glm::vec3 _scale = glm::vec3(0,0,0);
public:
    Enemy(const char *path, glm::vec3 position, glm::vec3 scale){
        _position = position;
        _scale = scale;
        loadModel(path);
    }
    void DrawEnemy(Player &player, Camera &camera, Shader &shader);
};


