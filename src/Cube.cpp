//
// Created by leodlplq on 16/11/2021.
//
#include "Cube.hpp"

Cube::Cube(){
    build();
}

void Cube::build (){
    vertices = {  //                        POSITION          |                     COLOR         |          TEXTURES COORDS
            Vertex(glm::vec3(-0.5, -0.5, -0.5),glm::vec3(0, 0, 1), glm::vec2(0, 1)), // SOMMET 0
            Vertex(glm::vec3(0.5, -0.5, -0.5),glm::vec3(0, 0, 1), glm::vec2(1, 1)), // SOMMET 1
            Vertex(glm::vec3(-0.5, 0.5, -0.5),glm::vec3(0, 0, 1), glm::vec2(0, 0)), // SOMMET 2
            Vertex(glm::vec3(0.5, 0.5, -0.5),glm::vec3(0, 0, 1), glm::vec2(1, 0)), // SOMMET 3
            Vertex(glm::vec3(-0.5, -0.5, 0.5),glm::vec3(0, 0, 1), glm::vec2(0, 1)), // SOMMET 4
            Vertex(glm::vec3(0.5, -0.5, 0.5),glm::vec3(0, 0, 1), glm::vec2(1, 1)), // SOMMET 5
            Vertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec3(0, 0, 1), glm::vec2(0, 0)), // SOMMET 6
            Vertex(glm::vec3(0.5, 0.5, 0.5),glm::vec3(0, 0, 1), glm::vec2(1, 0)) // SOMMET 7
    };
}

