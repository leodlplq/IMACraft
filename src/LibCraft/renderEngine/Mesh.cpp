////
//// Created by valentin on 10/12/2021.
////
//
#include "LibCraft/renderEngine/include/Mesh.hpp"

// constructor
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Textures> textures):
_vao(),
_vbo({}, 0),
_ibo({}, 0)
{
    this->_vertices = vertices;
    this->_indices = indices;
    this->_textures = textures;
    setupMesh();
}

// Initializes the Mesh
// (called in Mesh constructor)
void Mesh::setupMesh()
{
    _vao.bind();
    _vbo = vbo(&_vertices[0], static_cast<GLsizeiptr>(_vertices.size() * sizeof(Vertex)));
    _ibo = ibo(&_indices[0], static_cast<GLsizeiptr>(_indices.size() * sizeof(GLuint)));
    _vao.linkAttrib(_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, Position));
    _vao.linkAttrib(_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, Normal));
    _vao.linkAttrib(_vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, TexCoords));
    _vao.unbind();
    _vbo.unbind();
    _ibo.unbind();
}

// Draw the Mesh
void Mesh::Draw(Shader &shader)
{
    unsigned int diffuseNr = 1;
    unsigned int metallicRoughnessNr = 1;
    for(unsigned int i = 0; i < _textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding

        // Retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = _textures[i].type;
        /*
            /!\
                For this to work texture have to be named like this :
                    texture_diffuseN
                        OR
                    texture_metallicRoughnessN
                N beeing the number id of the texture
            /!\

        */
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_metallicRoughness")
            number = std::to_string(metallicRoughnessNr++);

        glUniform1i(glGetUniformLocation(shader._id, (name + number).c_str()), i);
        //shader.setInt((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, _textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // Draw mesh
    _vao.bind();
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    _vao.unbind();
}