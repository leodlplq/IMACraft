//
// Created by leodlplq on 16/11/2021.
//
#include "LibCraft/renderEngine/include/Cube.hpp"

Cube::Cube(const float radius) :
_placement(glm::mat4())
{
    build(radius);
}

Cube::Cube(const float x, const float y, const float z) :
_placement(1)
{
    _placement = glm::translate(_placement, glm::vec3(x,z,y));

}

void Cube::build (const float r){
    vertices = {  //                        POSITION          |                     NORMAL         |          TEXTURES COORDS
            Vertex(glm::vec3(-0.5*r, -0.5*r, 0.5*r),glm::vec3(0, 0, 1), glm::vec2(0, 1)), // SOMMET 0        7--------6
            Vertex(glm::vec3(0.5*r, -0.5*r, 0.5*r),glm::vec3(0, 0, 1), glm::vec2(1, 1)), // SOMMET 1        /|       /|
            Vertex(glm::vec3(0.5*r, -0.5*r, -0.5*r),glm::vec3(0, 0, 1), glm::vec2(0, 1)), // SOMMET 2      4--------5 |
            Vertex(glm::vec3(-0.5*r, -0.5*r, -0.5*r),glm::vec3(0, 0, 1), glm::vec2(1, 1)), // SOMMET 3     | |      | |
            Vertex(glm::vec3(-0.5*r, 0.5*r, 0.5*r),glm::vec3(0, 0, 1), glm::vec2(0, 0)), // SOMMET 4       | 3------|-2
            Vertex(glm::vec3(0.5*r, 0.5*r, 0.5*r),glm::vec3(0, 0, 1), glm::vec2(1, 0)), // SOMMET 5        |/       |/
            Vertex(glm::vec3(0.5*r, 0.5*r, -0.5*r),glm::vec3(0, 0, 1), glm::vec2(0, 0)), // SOMMET 6       0--------1
            Vertex(glm::vec3(-0.5*r, 0.5*r, -0.5*r),glm::vec3(0, 0, 1), glm::vec2(1, 0)) // SOMMET 7
    };
}






