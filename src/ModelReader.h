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

typedef struct
{
    unsigned char* data;
    int width;
    int height;
    int components;
}texture_data;



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
public:
    ModelReader(const char* path) { loadModel(path); gammaCorrection = 0; }
	
    std::vector<Mesh> getMeshes() const;

    static texture_data loadTexture(std::string file_name);
    static void freeTexture(texture_data texture);
	
    ~ModelReader();
};

