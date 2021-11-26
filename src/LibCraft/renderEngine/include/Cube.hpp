//
// Created by leodlplq on 16/11/2021.
//
#pragma once
#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "vector"
#include "glm/glm.hpp"
#include "LibCraft/renderEngine/include/Vertex.hpp"
#include "glm/gtc/matrix_transform.hpp"



class Cube {
public:
    Cube(const float radius = 1.0);
    Cube(const float x, const float y, const float z);
    Cube(const Cube& ) = default;

    void build(const float radius =1.0);
    //renvoie ptr sur data
    Vertex* getDataPointer() {
        return &vertices[0];
    }

    inline glm::mat4 getObjectMatrix() const{
        return _placement;
    };

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
            // Right
            1, 2, 6,
            6, 5, 1,
            // Left
            0, 4, 7,
            7, 3, 0,
            // Top
            4, 5, 6,
            6, 7, 4,
            // Bottom
            0, 3, 2,
            2, 1, 0,
            // Back
            0, 1, 5,
            5, 4, 0,
            // Front
            3, 7, 6,
            6, 2, 3
    }; // On peut le mettre directement en attribut vu qu'on va construire nos cubes toujours de la même façon
    int c_VertexCount = 36;
    glm::mat4 _placement;
};
