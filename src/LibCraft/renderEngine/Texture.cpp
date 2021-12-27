//
// Created by leodlplq on 20/11/2021.
//

#include "LibCraft/renderEngine/include/Texture.hpp"

Texture::Texture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    _type = texType;
    int widthImg, heightImg, nomColCh;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &nomColCh, 0);

    GLuint texture;
    glGenTextures(1, &_id);
    glActiveTexture(slot);
    glBindTexture(texType, _id);

    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);

    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char *uniform, GLuint unit) {
    GLuint tex0Uni = glGetUniformLocation(shader._id, uniform);
    shader.activate();
    glUniform1i(tex0Uni, unit);
}

void Texture::bind(){
    glBindTexture(_type, _id);
}

void Texture::unbind(){
    glBindTexture(_type, 0);
}

void Texture::deleteTex() {
    glDeleteTextures(1, &_id);
}