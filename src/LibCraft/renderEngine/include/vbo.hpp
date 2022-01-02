//
// Created by leodlplq on 18/11/2021.
//
#pragma once
#include "Vertex.hpp"
#include "Vertex2D.hpp"
#include "glad/glad.h"

class vbo {
public:
    GLuint _id;
    vbo(Vertex* vertices, GLsizeiptr size);
    vbo(Vertex2D* vertices, GLsizeiptr size);
    vbo() = default;
    void bind();
    void unbind();
    void deleteVbo();
};

