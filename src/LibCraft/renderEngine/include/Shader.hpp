//
// Created by leodlplq on 18/11/2021.
//
#pragma once

#include <glad/glad.h>

#include "LibCraft/tools/include/filePath.hpp"
#include "LibCraft/tools/include/getFIleContent.hpp"


class Shader {
public:
    GLuint _id;
    Shader(const char* vertexFile, const char* fragmentFile, FilePath appPath);
    ~Shader() = default;


    void activate();
    void deleteShader();

private:
    void compileErrors(unsigned int shader, const char *type);
};



