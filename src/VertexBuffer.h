#pragma once
#include <vector>
#include "GL/glew.h"
#include "glm/glm.hpp"

#include <iostream>

#include "Mesh.h"

class VertexBuffer
{
	GLuint Vao_;
	std::vector<GLuint> Buffers;
	std::vector<GLuint> Textures;
	GLuint indexBuffer = 0;
	GLuint indexCount = 0;
	void bindArrayObject();
public:
	VertexBuffer();
	VertexBuffer(const VertexBuffer&) = delete;
	~VertexBuffer();

	void drawObj(GLenum type = GL_TRIANGLES, GLenum textureType = GL_TEXTURE_2D);

	void addTextureBuffer(std::string filename);
	void addCubeMapBuffer(std::vector<std::string>faces_name);
	
	void addVertexBuffer(const std::vector<GLfloat>& data);
	void addVertexBuffer(const std::vector<glm::vec2>& data);
	void addVertexBuffer(const std::vector<glm::vec3>& data);
	void addVertexBuffer(const std::vector<glm::vec4>& data);
	void addIndices(const std::vector<GLuint>& data);
};

