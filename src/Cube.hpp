//
// Created by leodlplq on 16/11/2021.
//
#pragma once
#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "vector"
#include "glm/glm.hpp"
#include "LibCraft/renderEngine/Vertex.hpp"



class Cube {
public:
    Cube();
    void build();
    //renvoie ptr sur data
    Vertex* getDataPointer() {
        return &vertices[0];
    }

    // Renvoie le nombre de vertex
    GLsizei getVertexCount() const {
        return c_VertexCount;
    }

    GLuint* getIndices() {
        return &indices[0];
    }

private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices = {
            0, 1, 2, 3,1,2,4,5,6,7,5,6,0,2,4,2,4,6,1,3,5,3,5,7,2,3,6,3,6,7,0,1,4,1,4,5
    }; // On peut le mettre directement en attribut vu qu'on va construire nos cubes toujours de la même façon
    const int c_VertexCount = 36;
};
