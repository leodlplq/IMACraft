//
// Created by valentin on 24/11/2021.
//
#pragma
//#include "LibCraft/renderEngine/include/Texture.hpp"
#include "string"
#include "LibCraft/renderEngine/include/Shader.hpp"
#include "stb/stb_image.h"
#include "LibCraft/tools/include/filePath.hpp"
#include<glad/glad.h>

class TextureCube{
public:
    GLuint _id;
    GLenum _type;
    unsigned int _cubemapTexture;
    TextureCube(const char* rightpath, const char* leftpath,const char* toppath,const char* bottompath,const char* frontpath,const char* backpath);

    std::string _facesCubemap[6];

    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void bind();
    void unbind();
    void deleteTex();
};

