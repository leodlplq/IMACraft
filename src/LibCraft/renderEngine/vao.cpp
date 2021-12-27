//
// Created by leodlplq on 18/11/2021.
//

#include "LibCraft/renderEngine/include/vao.hpp"

vao::vao() {
    glGenVertexArrays(1, &_id);
}

void vao::linkAttrib(vbo& vbo, GLuint layout, GLint nbComponents, GLenum type, GLsizei stride, const GLvoid* offset) {
    vbo.bind();
    glVertexAttribPointer(layout, nbComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

void vao::bind() {
    glBindVertexArray(_id);
}

void vao::unbind() {
    glBindVertexArray(0);
}

void vao::deleteVao() {
    glDeleteVertexArrays(1, &_id);
}
