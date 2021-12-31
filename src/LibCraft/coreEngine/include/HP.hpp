//
// Created by Adam on 13/12/2021.
//
#pragma once

#include <iostream>
#include "vector"
#include "LibCraft/renderEngine/include/Vertex.hpp"
#include "LibCraft/renderEngine/include/Cube.hpp"
#include "LibCraft/renderEngine/include/vbo.hpp"
#include "LibCraft/renderEngine/include/vao.hpp"
#include "LibCraft/renderEngine/include/ibo.hpp"
#include "stb/stb_image.h"
#include "LibCraft/tools/include/filePath.hpp"

class HP {
public:
    HP();
    void drawHP();
    void genTexHP(std::string filePathHP);
    int getVertexCountHP() {
        return _vertices.size();
    }
    int getIndicesCountHP() {
        return _indices.size();
    }
    GLuint* getIndicesHP() {
        return &_indices[0];
    }
    Vertex* getDataPointerHP() {
        return &_vertices[0];
    }
    float getHP() {
        return _nbHearts;
    }
    void lossHP() {
        _nbHearts--;
    }
    ~HP();
private:
    std::vector<Vertex> _vertices = {
            Vertex(glm::vec2(-0.5, -0.5),glm::vec2(0.0, 0.0)),
            Vertex(glm::vec2(0.5, -0.5), glm::vec2(1.0, 0.0)),
            Vertex(glm::vec2(0.5, 0.5),  glm::vec2(1.0, 1.0)),
            Vertex(glm::vec2(-0.5, 0.5), glm::vec2(0.0, 1.0))
    };
    std::vector<GLuint> _indices = {0, 1, 2, 0, 2, 3};
    vao _vao;
    vbo _vbo;
    ibo _ibo;
    GLuint _texture;
    float _nbHearts = 10;
};
