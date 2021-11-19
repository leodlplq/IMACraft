//
// Created by leodlplq on 18/11/2021.
//
#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <filesystem>

std::string get_file_contents(const char* filename);

class Shader {
public:
    GLuint _id;
    Shader(const char* vertexFile, const char* fragmentFile);

    void activate();
    void deleteShader();
};



