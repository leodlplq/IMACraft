//
// Created by valentin on 24/11/2021.
//
#include "LibCraft/renderEngine/include/TextureCube.hpp"

TextureCube::TextureCube(const char* rightpath, const char* leftpath,const char* toppath,const char* bottompath,const char* frontpath,const char* backpath, const GLenum format)
:_facesCubemap{rightpath,leftpath,toppath,bottompath,frontpath,backpath}{
    _type = GL_TEXTURE_CUBE_MAP;
    glGenTextures(1,&_cubemapTexture);
    glBindTexture(_type, _cubemapTexture);
    glTexParameteri(_type,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(_type,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(_type,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(_type,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(_type,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);

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
                            format,
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
    glBindTexture(_type, 0);
}

void TextureCube::bind(){
    glBindTexture(_type, _cubemapTexture);
}
