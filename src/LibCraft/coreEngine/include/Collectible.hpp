//
// Created by valentin on 24/12/2021.
//
#pragma once
#include "../src/LibCraft/renderEngine/include/Model.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../src/LibCraft/renderEngine/include/Shader.hpp"
#include "../src/LibCraft/renderEngine/include/Camera.hpp"

class Collectible {
public:
    bool _alive = true;
    Collectible(const char *path, glm::vec3 position){
        Model model(path);
        _model = model;
        _position = position;
    }

    Model getModel(){
        return _model;
    }
    glm::vec3 getPosition(){
        return _position;
    }

    void Draw(Shader &shader, Camera &camera);

    void Update(Player &player);

private:
    Model _model;
    glm::vec3 _position = glm::vec3(0,0,0);
    float _angle =0.0f;
};

