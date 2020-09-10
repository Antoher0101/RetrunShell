#include "VertexBuffer.h"

#include <stb/stb_image.h>

void VertexBuffer::drawObj(GLenum type, GLenum textureType)
{
	assert(indexBuffer != 0);
	
	bindArrayObject();
	for (GLuint i = 0; i < Buffers.size(); i++)
		glEnableVertexAttribArray(i);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDrawElements(type, indexCount, GL_UNSIGNED_INT, nullptr);
	for (GLuint i = 0; i < Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(textureType, Textures[i]);
	}
	for (GLuint i = 0; i < Buffers.size(); i++)
		glDisableVertexAttribArray(i);
}

void VertexBuffer::addTextureBuffer(std::string filename)
{
	std::string tex_path = "resource/model/textures/" + filename;
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	int width, height, nrComponents;
	
	unsigned char* data = stbi_load(tex_path.c_str(), &width, &height, &nrComponents, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture load error!" << std::endl;
	}
	
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	Textures.emplace_back(texture);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

void VertexBuffer::addCubeMapBuffer(std::vector<std::string> faces_name)
{
	const std::string face_path = "resource/model/textures/skybox/";
	for (size_t i = 0; i < faces_name.size(); i++)
		faces_name[i].insert(0, face_path);
	
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces_name.size(); i++)
	{
		unsigned char* data = stbi_load(faces_name[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces_name[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//GL_LINEAR
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	Textures.emplace_back(texture);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
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

void VertexBuffer::bindArrayObject()
{
	glBindVertexArray(Vao_);
}

VertexBuffer::VertexBuffer()
{
	glGenVertexArrays(1, &Vao_);
	bindArrayObject();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(Buffers.size(), Buffers.data());
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &Vao_);
	glDeleteTextures(Textures.size(), Textures.data());
}
