//
// Created by valentin on 23/11/2021.
//
#pragma once
#include "Cube.hpp"
#include "string"
#include "iostream"
#include "stb/stb_image.h"
#include "vao.hpp"
#include "vbo.hpp"
#include "ibo.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

class Skybox : public Cube{

public:
    vao _vao;
    vbo _vbo;
    ibo _ibo;

    GLuint _id;
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
    void draw(){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    void setup(Shader& shader, Camera& camera, int width, int height);

};


