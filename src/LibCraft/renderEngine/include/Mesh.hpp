//
// Created by valentin on 10/12/2021.
//
#pragma once

#include "vbo.hpp"
#include "vao.hpp"
#include "ibo.hpp"
#include "Texture.hpp"
#include "TextureCube.hpp"
#include "Cube.hpp"

class Mesh {
public:
    vao _vao; // A mettre en privé quand Player sera mieux défini

    Mesh(Cube mesh, std::string filePathRight, std::string filePathLeft, std::string filePathTop, std::string filePathBottom, std::string filePathFront, std::string filePathBack, GLenum format);
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Texture tex):
    _vao(),
    _vbo({}, 0),
    _ibo({}, 0),
    _mesh(0),
    _texturecube(),
    _vertices(vertices),
    _indices(indices)
    {
        setupMesh();
    };
    void draw(){
        _vao.bind();
        _texturecube.bind();
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    }

    void del(){
        _vao.deleteVao();
        _vbo.deleteVbo();
        _ibo.deleteIbo();
    }
    void setupMesh();

private:
    vbo _vbo;
    ibo _ibo;
    TextureCube _texturecube;
    Cube _mesh;
    std::vector<Vertex> _vertices;
    std::vector<GLuint> _indices={
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
    };

};



