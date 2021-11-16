//
// Created by leodlplq on 16/11/2021.
//

#pragma once
#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "vector"


class Triangle {
public:
    Triangle();
    void build();

    //renvoie ptr sur data
    const GLfloat* getDataPointer() const {
        return &t_Vertices[0];
    }

    // Renvoit le nombre de vertex
    GLsizei getVertexCount() const {
        return t_VertexCount;
    }



private:
    std::vector<GLfloat> t_Vertices;
    GLsizei t_VertexCount;
};

