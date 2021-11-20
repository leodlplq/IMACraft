//
// Created by leodlplq on 20/11/2021.
//

#pragma once

#include<glad/glad.h>
#include "../lib/stb/stb.h"
#include "Shader.hpp"
#include "../tools/filePath.hpp"

class Texture {
public:
    GLuint _id;
    GLenum _type;

    Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void bind();
    void unbind();
    void deleteTex();

};

