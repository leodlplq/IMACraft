//
// Created by valentin on 24/11/2021.
//
#pragma once
//#include "LibCraft/renderEngine/include/Texture.hpp"
#include <array>
#include "LibCraft/renderEngine/include/Shader.hpp"
#include "stb/stb_image.h"
#include "LibCraft/tools/include/filePath.hpp"
#include<glad/glad.h>
#include "Texture.hpp"

class TextureCube : public Texture{
public:
    unsigned int _cubemapTexture;
    TextureCube(const char* rightpath, const char* leftpath,const char* toppath,const char* bottompath,const char* frontpath,const char* backpath, const GLenum format);
    TextureCube() = default;
    std::array<std::string,6>_facesCubemap;

    void bind();
};

