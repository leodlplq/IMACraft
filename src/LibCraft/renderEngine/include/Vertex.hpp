//
// Created by valentin on 20/11/2021.
//
#pragma once
#include <glm/glm.hpp>
#include <string>


struct Vertex {
    glm::vec3 Position;
    glm::vec2 TexCoords;
    glm::vec3 Normal;
    Vertex(glm::vec3 vec1, glm::vec3 vec2, glm::vec2 vec3):
            Position(vec1), Normal(vec2), TexCoords(vec3){}
    Vertex(): Position(), Normal(), TexCoords(){}
};

struct Textures {
    unsigned int id;
    std::string type;
    std::string path;
};


struct Material {
    //Material color lighting
    glm::vec4 Ka;
    //Diffuse reflection
    glm::vec4 Kd;
    //Mirror reflection
    glm::vec4 Ks;
};

