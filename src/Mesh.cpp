#include "Mesh.h"

std::vector<Vertex> Mesh::getVertexData() const
{
    return vertices_;
}

std::vector<glm::vec3> Mesh::getVertexPos() const
{
    std::vector<glm::vec3> temp_vec;
    for (size_t i = 0; i < vertices_.size(); i++)
        temp_vec.emplace_back(vertices_[i].Position);
    return temp_vec;
}

std::vector<glm::vec2> Mesh::getTexCoords() const
{
    std::vector<glm::vec2> temp_vec;
    for (size_t i = 0; i < vertices_.size(); i++)
        temp_vec.emplace_back(vertices_[i].TexCoords);
    return temp_vec;;
}

std::vector<glm::vec3> Mesh::getVertexNormals() const
{
    std::vector<glm::vec3> temp_vec;
    for (size_t i = 0; i < vertices_.size(); i++)
        temp_vec.emplace_back(vertices_[i].Normal);
    return temp_vec;
}

std::vector<unsigned int> Mesh::getIndeces() const
{
    return indices_;
}
