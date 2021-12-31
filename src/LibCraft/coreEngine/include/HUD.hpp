//
// Created by valentin on 26/12/2021.
//
#pragma once
#include "../src/LibCraft/renderEngine/include/Model.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../src/LibCraft/renderEngine/include/Shader.hpp"
#include "../src/LibCraft/renderEngine/include/Text.hpp"


class HUD: public Model{
public:
    HUD(int width, int height):_width(width),_height(height){};
    void DrawHUD(Shader &shader, Model hud, Model icon, int score, Text text, Shader &textShader);
    void DrawGameOver(Shader &shader, Model gameOver);
    inline std::string getScore() const{ return _score;}
    inline glm::vec3 getFontColor() const {return _colorHud;}
private:
    float _angle = 0;
    int _width;
    int _height;
    std::string _score;
    glm::vec3 _colorHud = glm::vec3(255.f/255.f, 255.f/255.f, 255.f/255.f);


};



