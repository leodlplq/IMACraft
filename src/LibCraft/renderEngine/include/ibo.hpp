//
// Created by leodlplq on 18/11/2021.
//
#pragma once

#include "glad/glad.h"

class ibo {
public:

    ibo() = default;
    GLuint _id;
    ibo(GLuint* indices, GLsizeiptr size);
    void bind();
    void unbind();
    void deleteIbo();
};

