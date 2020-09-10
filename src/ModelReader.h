#pragma once
#include <string>
#include <vector>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Mesh.h"
class ModelReader
{
    std::vector<Mesh> meshes;
    std::string directory;

    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    std::vector<Texture> textures_loaded;

    bool gammaCorrection;
	
    void loadModel(std::string name);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
public:
    ModelReader(const char* path) { loadModel(path); gammaCorrection = 0; }
    void setTexture(std::string name);
    std::vector<Mesh> getMeshes() const;
    ~ModelReader();
};

