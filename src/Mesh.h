#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
	std::vector<Vertex>       vertices_;
	std::vector<unsigned int> indices_;
	std::vector<Texture>      textures_;
	
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures) :
	vertices_(vertices),
	indices_(indices),
	textures_(textures)
	{}
	
	std::vector<Vertex> getVertexData() const;
    std::vector<glm::vec3> getVertexPos() const;
    std::vector<glm::vec2> getTexCoords() const;
    std::vector<glm::vec3> getVertexNormals() const;
	std::vector<unsigned int> getIndeces() const;
};
