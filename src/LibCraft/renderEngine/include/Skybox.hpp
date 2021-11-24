//
// Created by valentin on 23/11/2021.
//
#include "Cube.hpp"
#include "string"
#include "iostream"
#include "stb/stb_image.h"

class Skybox : public Cube{

public:
    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    unsigned int _cubemapTexture;
    std::string _facesCubemap[6] =
            {
                    "assets/textures/skybox/right.jpg",
                    "assets/textures/skybox/left.jpg",
                    "assets/textures/skybox/top.jpg",
                    "assets/textures/skybox/bottom.jpg",
                    "assets/textures/skybox/front.jpg",
                    "assets/textures/skybox/back.jpg",
            };
    Skybox();

};


