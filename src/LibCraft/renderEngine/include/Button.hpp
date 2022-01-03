//
// Created by leodlplq on 30/12/2021.
//

#pragma once

#include <string>
#include <functional>

//TOOLS
#include "LibCraft/tools/include/countSpaceInString.hpp"
//RENDER
#include "LibCraft/renderEngine/include/Text.hpp"
#include "LibCraft/renderEngine/include/Rectangle.hpp"
#include "LibCraft/renderEngine/include/vbo.hpp"
#include "LibCraft/renderEngine/include/vao.hpp"
#include "LibCraft/renderEngine/include/ibo.hpp"



class Button {
public:
    //CONSTRUCTORS AND DESTRUCTORS
    Button() = default;
    Button(unsigned int scene, std::string text, int &windowHeight, int &windowWidth, int x, int y, float paddingWidth, float paddingHeight, float scale, glm::vec3 colorBackground, glm::vec3 colorText, Text &font, Shader &shaderText, Shader &shaderBackground, std::function<void()> &func);
    ~Button() = default;

    //USEFUL
    void render();
    void setup(Rectangle &rectangle);
    void draw(Rectangle &rect);

    float getWidth();
    float getHeight();
    inline unsigned int getSceneNb() const {return _scene; }

    //COLOR THINGS
    inline void changeBackgroundColor(glm::vec3 newBg) {_backgroundColor = newBg; }
    inline void changeFontColor(glm::vec3 newBg) {_textColor = newBg;}

    //EVENT
    bool isHovered(double &xPos,double &yPos);

    //CLICK EVENT
    std::function<void()> _clickCallback;

private:
    int _windowHeight, _windowWidth;
    float _x, _y;
    float _paddingWidth, _paddingHeight;
    float _scale;
    std::string _text;
    glm::vec3 _backgroundColor, _textColor;
    Text _font;
    Shader _shaderText;
    Shader _shaderBackground;

    vao _vao;
    vbo _vbo;
    ibo _ibo;

    unsigned int _scene;


};
