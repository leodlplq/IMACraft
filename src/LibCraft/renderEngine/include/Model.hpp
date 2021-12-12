//
// Created by valentin on 12/12/2021.
//

#pragma once
#include "Texture.hpp"
#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
    Model(char *path)
    {
        loadModel(path);
    }
    void draw()
    {
        for(unsigned int i = 0; i < meshes.size()-1; i++) // ATTENTION -1 JUSTE POUR LE SPACE MARINE
            meshes[i].draw();
    }
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};

