//
// Created by leodlplq on 18/11/2021.
//
#pragma once
#include "Vertex.hpp"
#include "glad/glad.h"

class vbo {
public:
    GLuint _id;
    vbo(Vertex* vertices, GLsizeiptr size);

    void bind();
    void unbind();
    void deleteVbo();
};

