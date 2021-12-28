//
// Created by leodlplq on 18/11/2021.
//

#include "LibCraft/renderEngine/include/ibo.hpp"

ibo::ibo(GLuint *vertices, GLsizeiptr size) {
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}


void ibo::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void ibo::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ibo::deleteIbo() {
    glDeleteBuffers(1, &_id);
}
