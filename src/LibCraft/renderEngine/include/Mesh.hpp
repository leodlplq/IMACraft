//
// Created by valentin on 10/12/2021.
//

#pragma once

#include "Shader.hpp"
#include "Vertex.hpp"
#include "vbo.hpp"
#include "vao.hpp"
#include "ibo.hpp"
#include <assimp-5.0.1/include/assimp/Importer.hpp>
#include <assimp-5.0.1/include/assimp/scene.h>
#include <assimp-5.0.1/include/assimp/postprocess.h>
#include <assimp-5.0.1/include/assimp/pbrmaterial.h>

#include <glm/glm.hpp>
#include "../lib/stb/stb_image.h"

#include <vector>
#include <string>

class Mesh {
public :
    // Mesh data
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<Textures> _textures;
    // Constructor
    Mesh (std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Textures> textures);
    void Draw (Shader &shader);

private :
    // Render data
    vao _vao;
    vbo _vbo;
    ibo _ibo;
    void setupMesh();
};

