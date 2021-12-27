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
    Shader(const char* vertexFile, const char* fragmentFile, const FilePath& appPath);

    void activate() const;
    void deleteShader() const;

private:
    static void compileErrors(unsigned int shader, const char *type);
};



