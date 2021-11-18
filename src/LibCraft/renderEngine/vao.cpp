//
// Created by leodlplq on 18/11/2021.
//

#include "vao.hpp"

vao::vao() {
    glGenVertexArrays(1, &_id);
}

void vao::linkVBO(vbo vbo, GLuint layout) {
    vbo.bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
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
