#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned>& indices, std::vector<Texture>& textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
}

std::vector<Vertex> Mesh::getVertexData() const
{
    return vertices;
}

std::vector<glm::vec3> Mesh::getVertexPos() const
{
    std::vector<glm::vec3> temp_vec;
    for (size_t i = 0; i < vertices.size(); i++)
        temp_vec.emplace_back(vertices[i].Position);
    return temp_vec;
}

std::vector<glm::vec2> Mesh::getTexCoords() const
{
    std::vector<glm::vec2> temp_vec;
    for (size_t i = 0; i < vertices.size(); i++)
        temp_vec.emplace_back(vertices[i].TexCoords);
    return temp_vec;;
}

std::vector<glm::vec3> Mesh::getVertexNormals() const
{
    std::vector<glm::vec3> temp_vec;
    for (size_t i = 0; i < vertices.size(); i++)
        temp_vec.emplace_back(vertices[i].Normal);
    return temp_vec;
}

std::vector<unsigned int> Mesh::getIndeces() const
{
    return indices;
}
