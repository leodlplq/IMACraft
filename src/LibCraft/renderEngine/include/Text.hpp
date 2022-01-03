//
// Created by leodlplq on 29/12/2021.
//
#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cassert>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
//TOOLS
#include "LibCraft/tools/include/filePath.hpp"
//RENDER
#include "LibCraft/renderEngine/include/Shader.hpp"




struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class Text {

public:
    //CONSTRUCTORS AND DESTRUCTORS
    Text() = default;
    Text(const FilePath &filePath, int width, int height,std::string fontName);
    ~Text() = default;

    void init(const FilePath &filePath);
    void renderText(Shader &s, std::string text, float x, float y, float scale, glm::vec3 color);
    float textWidth(std::string text, float scale);
    float textHeight(std::string text, float scale);


private:
    int _wHeight, _wWidth;
    std::string _fontName;
    unsigned int _VAO, _VBO;
    std::map<char, Character> Characters;


};




