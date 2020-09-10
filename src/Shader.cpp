#include "Shader.h"

GLuint Shader::loadShader(const std::string& path, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	std::ifstream fs(path);
	std::string shaderCode = { std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>() };
	const char* c = shaderCode.c_str();
	glShaderSource(shader, 1, &c, nullptr);

	glCompileShader(shader);
	
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	char buf[0x1000];
	GLsizei len;
	glGetShaderInfoLog(shader, sizeof buf, &len, buf);
	if(len>0)
	{
		std::cout << path << ":\n" << buf <<std::endl;
	}
	if (!status) {
		throw std::runtime_error("could not compile shader: " + path);
	}

	return shader;
}

void Shader::link()
{
	glAttachShader(program_, vertexShader);
	glAttachShader(program_, fragmentShader);
	glLinkProgram(program_);
}

void Shader::bindAttrib(GLuint index,const std::string& name)
{
	glBindAttribLocation(program_, index, name.c_str());
}

void Shader::setShader()
{
	glUseProgram(program_);
}

// Uniform overloads
void Shader::setUniform(const std::string& name, float value1, float value2)
{
	glUniform2f(getLocation(name), value1,value2);
}
void Shader::setUniform(const std::string& name, float value)
{
	glUniform1f(getLocation(name), value);
}
void Shader::setUniform(const std::string& name, glm::mat4 value)
{
	glUniformMatrix4fv(getLocation(name), 1,GL_FALSE, glm::value_ptr(value));
}
void Shader::setUniform(const std::string& name, glm::vec3 value)
{
	glUniform3fv(getLocation(name),1,glm::value_ptr(value));
}
void Shader::setUniform(const std::string& name, glm::vec4 value)
{
	glUniform4fv(getLocation(name), 1, glm::value_ptr(value));
}

GLint Shader::getLocation(const std::string& name)
{
	return glGetUniformLocation(program_, name.c_str());
}

Shader::Shader(const std::string& name)
{
	program_ = glCreateProgram();
	vertexShader = loadShader("resource/glsl/" + name + ".vert", GL_VERTEX_SHADER);
	fragmentShader = loadShader("resource/glsl/" + name + ".frag", GL_FRAGMENT_SHADER);
	
}

Shader::~Shader()
{
	glDetachShader(program_, vertexShader);
	glDetachShader(program_, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(program_);
}