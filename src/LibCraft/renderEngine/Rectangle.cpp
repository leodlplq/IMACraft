//
// Created by leodlplq on 30/12/2021.
//

#include "LibCraft/renderEngine/include/Rectangle.hpp"

Rectangle::Rectangle(float x, float y, float width, float height, glm::vec3 &color):
_vertices()
{
    _vertices.push_back(Vertex(glm::vec3(x, y, 0), color, glm::vec2(0, 0)));
    _vertices.push_back(Vertex(glm::vec3(x + width, y, 0), color, glm::vec2(1, 0)));
    _vertices.push_back(Vertex(glm::vec3(x + width, y + height, 0), color, glm::vec2(1, 1)));
    _vertices.push_back(Vertex(glm::vec3(x, y + height, 0), color, glm::vec2(0, 1)));
    _vertices.push_back(Vertex(glm::vec3(x + width, y + height, 0), color, glm::vec2(1, 1)));
    _vertices.push_back(Vertex(glm::vec3(x, y, 0), color, glm::vec2(0, 0)));
}

std::vector<GLuint> Rectangle::getIndices() const {

    std::vector<GLuint> indices = {
            0, 1, 2, //TOP LEFT CORNER    0------------1
            //                            |            |
            2, 3, 0 //RIGHT BOTTOM CORNER 3------------2
    };

    return indices;
}


