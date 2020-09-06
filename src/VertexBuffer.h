#pragma once
#include <vector>
#include "GL/glew.h"
#include "glm/glm.hpp"

#include <iostream>

class VertexBuffer
{
	GLuint Vao_;
	std::vector<GLuint> Buffers;
	GLuint indexBuffer = 0;
	size_t indexCount = 0;
	void bindAo();
public:
	VertexBuffer();
	VertexBuffer(const VertexBuffer&) = delete;
	~VertexBuffer();

	void drawObj(GLenum type = GL_TRIANGLES);
	void addVertexBuffer(const std::vector<GLfloat>& data);
	void addVertexBuffer(const std::vector<glm::vec2>& data);
	void addVertexBuffer(const std::vector<glm::vec3>& data);
	void addVertexBuffer(const std::vector<glm::vec4>& data);
	void addIndices(const std::vector<GLuint>& data);
};

