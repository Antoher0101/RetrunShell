#include "VertexBuffer.h"

void VertexBuffer::drawObj(GLenum type)
{
	assert(indexBuffer != 0);
	
	bindAo();
	
	for (GLuint i = 0; i < Buffers.size(); i++)
	{
		glEnableVertexAttribArray(i);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDrawElements(type, indexCount, GL_UNSIGNED_INT, nullptr);
	
	for (GLuint i = 0; i < Buffers.size(); i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void VertexBuffer::addVertexBuffer(const std::vector<GLfloat>& data)
{
	GLuint Vbo;
	glGenBuffers(1, &Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, Vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(Buffers.size(), 1, GL_FLOAT, GL_FALSE, 0, nullptr);
	Buffers.emplace_back(Vbo);
}

void VertexBuffer::addVertexBuffer(const std::vector<glm::vec2>& data)
{
	GLuint Vbo;
	glGenBuffers(1, &Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, Vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(Buffers.size(), 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	Buffers.emplace_back(Vbo);
}

void VertexBuffer::addVertexBuffer(const std::vector<glm::vec3>& data)
{
	GLuint Vbo;
	glGenBuffers(1, &Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, Vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(Buffers.size(), 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	Buffers.emplace_back(Vbo);
}

void VertexBuffer::addVertexBuffer(const std::vector<glm::vec4>& data)
{
	GLuint Vbo;
	glGenBuffers(1, &Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, Vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec4), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(Buffers.size(), 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	Buffers.emplace_back(Vbo);
}

void VertexBuffer::addIndices(const std::vector<GLuint>& data)
{
	assert(indexBuffer == 0);

	indexCount = data.size();
	
	glGenBuffers(1, &indexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), GL_STATIC_DRAW);
}

void VertexBuffer::bindAo()
{
	glBindVertexArray(Vao_);
}

VertexBuffer::VertexBuffer()
{
	glGenVertexArrays(1, &Vao_);
	bindAo();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(Buffers.size(), Buffers.data());
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &Vao_);
}
