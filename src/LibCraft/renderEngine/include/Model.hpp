//
// Created by valentin on 12/12/2021.
//
#pragma once
#include "Mesh.hpp"

class Model {
public :
    Model(const char *path) {
        loadModel(path);
    }
    Model() {}
    void Draw(Shader &shader);

    float getHeight();
    void loadModel(std::string path);

private:
    std::vector<Mesh> meshes; // Vector of meshes constituting the Model
    std::string directory; // File location
    //void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Textures> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};
