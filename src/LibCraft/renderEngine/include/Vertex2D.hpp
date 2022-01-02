//
// Created by Adam on 01/01/2022.
//
#pragma once
#include <glm/glm.hpp>

struct Vertex2D {
    glm::vec2 _position;
    glm::vec3 _color;
    glm::vec2 _texCoords;
    Vertex2D(glm::vec2 position, glm::vec3 color, glm::vec2 texCoords) :
            _position(position), _color(color), _texCoords(texCoords){}
};
