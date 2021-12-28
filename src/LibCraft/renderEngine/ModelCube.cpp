//
// Created by valentin on 10/12/2021.
//

#include "LibCraft/renderEngine/include/ModelCube.hpp"

ModelCube::ModelCube(Cube mesh,std::string filePathRight, std::string filePathLeft, std::string filePathTop,std::string filePathBottom,std::string filePathFront,std::string filePathBack, GLenum format) :
        _vao(),
        _vbo({}, 0),
        _ibo({}, 0),
        _mesh(mesh),
        _texturecube(&filePathRight[0],&filePathLeft[0],&filePathTop[0],&filePathBottom[0],&filePathFront[0],&filePathBack[0], format)
{
    _vao.bind();
    _vbo = vbo(mesh.getDataPointer(),mesh.getVertexCount()*sizeof(Vertex));
    _ibo = ibo(mesh.getIndices(), mesh.getVertexCount()*sizeof (GLuint));
    _vao.linkAttrib(_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, Position));
    _vao.linkAttrib(_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, Normal));
    _vao.linkAttrib(_vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, TexCoords));
    _vao.unbind();
    _vbo.unbind();
    _ibo.unbind();
}