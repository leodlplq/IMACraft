//
// Created by valentin on 20/11/2021.
//
#pragma once
#include "glm/glm.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoords;
    Vertex(glm::vec3 vec1, glm::vec3 vec2, glm::vec2 vec3):
            position(vec1),color(vec2),texCoords(vec3){}
    Vertex():position(),color(),texCoords(){}
};

