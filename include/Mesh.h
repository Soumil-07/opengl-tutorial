#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Shader.h"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture 
{
    unsigned int ID;
    std::string Type;
    std::string Path;
};

struct Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) :
        vertices(vertices), indices(indices), textures(textures)
    {
        setupMesh();
    }

    void Draw(Shader& shader);

private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

