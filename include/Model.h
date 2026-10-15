#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "assimp/material.h"
#include "assimp/mesh.h"

#include <string>
#include <vector>

#include <assimp/scene.h>

class Model 
{
public:
    Model(const std::string& path)
    {
        load(path);
    }

    void Draw(Shader& shader);

private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;

    void load(std::string path);

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
