#pragma once
#include <vector>
#include "GL/glew.h"
#include "glm/glm.hpp"

#include <iostream>

#include "Mesh.h"
#include "ModelReader.h"
#include "Text.h"

class VertexBuffer
{
	GLuint Vao_;
	std::vector<GLuint> Buffers;
	std::vector<GLuint> Textures;
	std::vector<GLuint> Glyphs;
	GLuint indexBuffer = 0;
	GLuint indexCount = 0;

	void bindArrayObject();
	
public:
	VertexBuffer();
	VertexBuffer(const VertexBuffer&) = delete;
	~VertexBuffer();

	void drawObj(GLenum type = GL_TRIANGLES, GLsizei primcount = 1, GLenum textureType = GL_TEXTURE_2D);
	void staticDraw();
	
	void addTextureBuffer(std::string filename);
	void addCubeMapBuffer(std::vector<std::string>faces_name);
	
	GLuint addGlyphTexture(FT_Face face);
	void updateBuffer(gltext::Glyph ch, std::vector<glm::vec4>& vertices);
	
	void addTextBuffer();
	void addVertexBuffer(const std::vector<GLfloat>& data);
	void addVertexBuffer(const std::vector<glm::vec2>& data);
	void addVertexBuffer(const std::vector<glm::vec3>& data);
	void addVertexBuffer(const std::vector<glm::vec4>& data);
	void addIndices(const std::vector<GLuint>& data);

	void unbindBuffer();
};

