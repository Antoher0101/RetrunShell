#pragma once
#include "GL/glew.h"
#include "gl/GL.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"

#include <string>
#include <iostream>
#include <fstream>
class Shader
{
	GLuint program_;
	GLuint vertexShader;
	GLuint geometryShader;
	GLuint fragmentShader;
	
	bool geomFound;
	
	GLuint loadShader(const std::string& path, GLenum shaderType);
	GLint getLocation(const std::string& name);
public:
	void link();
	void bindAttrib(GLuint index, const std::string& name);
	void setShader();

	void setMaterial(material mat);
	
	void setUniform(const std::string& name, float value);
	void setUniform(const std::string& name, float value1, float value2);
	void setUniform(const std::string& name, glm::mat4 value);
	void setUniform(const std::string& name, glm::vec3 value);
	void setUniform(const std::string& name, glm::vec4 value);
	void setUniform(const std::string& name, int value);
	
	Shader(const std::string& name);
	~Shader();
};
