//
// Created by Adam on 13/12/2021.
//

#include "LibCraft/coreEngine/include/HP.hpp"

HP::HP() :
_vao(),
_vbo({}, 0),
_ibo({}, 0)
{
    _vao.bind();
    _vbo = vbo(this->getDataPointerHP(),this->getVertexCountHP()*sizeof(Vertex));
    _ibo = ibo(this->getIndicesHP(), this->getIndicesCountHP()*sizeof(GLuint));
    _vao.linkAttrib(_vbo, 3, 3, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, Position));
    _vao.linkAttrib(_vbo, 4, 3, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, Normal));
    _vao.linkAttrib(_vbo, 5, 2, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, TexCoords));
    _vao.unbind();
    _vbo.unbind();
    _ibo.unbind();
}

void HP::genTexHP(std::string filePathHearth) {
    glGenTextures(1, &_texture);
    glActiveTexture(_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filePathHearth.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void HP::drawHP(Shader &shader, int nbHp) {
    shader.activate();
    for (float i = 0; i < nbHp; i++) {
        glm::mat4 modelHP = glm::mat4(1.0);
        modelHP = glm::translate(modelHP, glm::vec3(0.09 + 0.4 * i / 10, -0.625, 0.0));
        modelHP = glm::scale(modelHP, glm::vec3(0.045f, 0.07f, 0.05f));
        glUniformMatrix4fv(glGetUniformLocation(shader._id, "modelHP"), 1, GL_FALSE, glm::value_ptr(modelHP));
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, _texture);
        _vao.bind();
        glDrawElements(GL_TRIANGLES, this->getIndicesCountHP(), GL_UNSIGNED_INT, 0);
    }
}

HP::~HP() {
    _vao.deleteVao();
    _vbo.deleteVbo();
    _ibo.deleteIbo();
}