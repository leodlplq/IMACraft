//
// Created by leodlplq on 18/11/2021.
//

#include "LibCraft/renderEngine/include/vbo.hpp"


vbo::vbo(Vertex *vertices, GLsizeiptr size) {
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void vbo::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void vbo::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vbo::deleteVbo() {
    glDeleteBuffers(1, &_id);
}
