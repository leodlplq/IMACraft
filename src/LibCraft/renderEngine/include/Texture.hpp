//
// Created by leodlplq on 20/11/2021.
//

#pragma once

#include<glad/glad.h>
#include "stb/stb_image.h"
#include "LibCraft/renderEngine/include/Shader.hpp"
#include "LibCraft/tools/include/filePath.hpp"

class Texture {
public:
    GLuint _id;
    GLenum _type;
    Texture() = default;
    Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void bind();
    void unbind();
    void deleteTex();

};
