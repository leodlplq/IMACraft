//
// Created by leodlplq on 18/11/2021.
//

#pragma once

#include <glad/glad.h>
#include "vbo.hpp"

class vao {
public:
    GLuint _id;
    vao();

    void linkAttrib(vbo& vbo, GLuint layout, GLint nbComponents, GLenum type, GLsizei stride, const GLvoid* offset);
    void bind();
    void unbind();
    void deleteVao();
};

