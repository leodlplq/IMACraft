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
    Collectible(const char *path, glm::vec3 position, unsigned int type, float value =0){
        Model model(path);
        _model = model;
        _position = position;
        _value = static_cast<int>(value);
        _type = type;
        _pos = position;
    }

    inline Model getModel() const{
        return _model;
    }
    inline glm::vec3 getPosition() const{
        return _position;
    }

    void Draw(Shader &shader, Camera &camera);
    inline void reset(){
        _alive = true;
        _position = _pos;
    }

    void Update(Player &player);
    inline void setAngle(float a){_angle = a;}
    inline float getAngle() const { return _angle;}

private:
    Model _model;
    glm::vec3 _position = glm::vec3(0,0,0);
    glm::vec3 _pos;
    float _angle =0.0f;
    int _value;
    unsigned int _type; // 0 : piece | 1 : apple
};

