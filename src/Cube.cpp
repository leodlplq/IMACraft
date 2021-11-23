//
// Created by leodlplq on 16/11/2021.
//
#include "Cube.hpp"

Cube::Cube() :
_placement(glm::mat4())
{
    build();
}

Cube::Cube(const float x, const float y, const float z) :
_placement(1)
{
    _placement = glm::translate(_placement, glm::vec3(x,z,y));

}

void Cube::build (){
    vertices = {  //                        POSITION          |                     COLOR         |          TEXTURES COORDS
            Vertex(glm::vec3(-0.5, -0.5, -0.5),glm::vec3(0, 0, 1), glm::vec2(0, 1)), // SOMMET 0
            Vertex(glm::vec3(0.5, -0.5, -0.5),glm::vec3(0, 0, 1), glm::vec2(1, 1)), // SOMMET 1
            Vertex(glm::vec3(-0.5, 0.5, -0.5),glm::vec3(0, 0, 1), glm::vec2(0, 0)), // SOMMET 2
            Vertex(glm::vec3(0.5, 0.5, -0.5),glm::vec3(0, 0, 1), glm::vec2(1, 0)), // SOMMET 3
            Vertex(glm::vec3(-0.5, -0.5, 0.5),glm::vec3(0, 0, 1), glm::vec2(1, 1)), // SOMMET 4
            Vertex(glm::vec3(0.5, -0.5, 0.5),glm::vec3(0, 0, 1), glm::vec2(0, 1)), // SOMMET 5
            Vertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec3(0, 0, 1), glm::vec2(1, 0)), // SOMMET 6
            Vertex(glm::vec3(0.5, 0.5, 0.5),glm::vec3(0, 0, 1), glm::vec2(0, 0)) // SOMMET 7
    };
}






