//
// Created by valentin on 23/11/2021.
//

#include "LibCraft/renderEngine/include/Skybox.hpp"


Skybox::Skybox():_vao(),
                 _vbo({}, 0),
                 _ibo({}, 0) {
    Cube skybox(2);
    _vao.bind();
    _vbo = vbo(skybox.getDataPointer(),skybox.getVertexCount()*sizeof(Vertex));
    _ibo = ibo(skybox.getIndices(), skybox.getVertexCount()*sizeof (GLuint));
    _vao.linkAttrib(_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, Position));
    _vao.linkAttrib(_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, Normal));
    _vao.linkAttrib(_vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, TexCoords));
    _vao.unbind();
    _vbo.unbind();
    _ibo.unbind();

    glGenTextures(1,&_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i<6; i++)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(_facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
        if(data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D
            (
                    GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0,
                    GL_RGB,
                    width,
                    height,
                    0,
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    data
                    );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load texture" << _facesCubemap[i] << std::endl;
            stbi_image_free(data);
        }
    }
}

void Skybox::setup(Shader& shader, Camera& camera, int width, int height)
{
    glDepthFunc(GL_LEQUAL);
    shader.activate();
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::mat4(glm::mat3(glm::lookAt(camera._position, camera._position + camera._orientation, camera._up)));
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader._id, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader._id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    _vao.bind();
    draw();
    // Switch back to the normal depth function
    glDepthFunc(GL_LESS);
}
