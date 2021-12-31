//
// Created by leodlplq on 30/12/2021.
//

#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
//RENDER
#include "LibCraft/renderEngine/include/Vertex.hpp"

class Rectangle {
public:
    //CONSTRUCTORS AND DESTRUCTORS
    Rectangle() = default;
    Rectangle(float x, float y, float width, float height, glm::vec3 &color);
    ~Rectangle() = default;

    //USEFUL
    std::vector<GLuint> getIndices() const;
    std::vector<Vertex> getVertices() const {return _vertices; }
    unsigned long getIndicesCount() const { return getIndices().size(); }


private:
    std::vector<Vertex> _vertices;
};
