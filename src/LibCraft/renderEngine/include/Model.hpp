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

class Model {
public:
    vao _vao; // A mettre en privé quand Player sera mieux défini

    Model(Cube mesh,std::string filePathRight, std::string filePathLeft, std::string filePathTop,std::string filePathBottom,std::string filePathFront,std::string filePathBack, GLenum format);

    void draw(){
        _vao.bind();
        _texturecube.bind();
        glDrawElements(GL_TRIANGLES, _mesh.getVertexCount(), GL_UNSIGNED_INT, 0);
    }
    void del(){
        _vao.deleteVao();
        _vbo.deleteVbo();
        _ibo.deleteIbo();
    }

    float getHeight() const {
        return _mesh.getHeight();
    }

private:
    vbo _vbo;
    ibo _ibo;
    TextureCube _texturecube;
    Cube _mesh;


};



