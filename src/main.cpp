#include "SFML/Graphics.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GL/GL.h"
#include "glm/glm.hpp"

#include <iostream>

#include "Events.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "ObjectReader.h"

int WIDTH = 1280;
int HEIGHT = 720;

sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"OpenGL", sf::Style::Default, sf::ContextSettings{ 24 });

int main(int argc, char* argv[])
{
	// Initializing GLFW and GLEW
	try
	{
		if (glfwInit() == GLFW_FALSE)
			throw std::runtime_error("Could not initialize GLFW");
	}
	catch (const std::exception &a)
	{
		std::cerr << a.what() << std::endl;
		throw;
	}
	try
	{
		if (glewInit() != GLEW_OK)
			throw std::runtime_error("Could not initialize GLEW");
	}
	catch (const std::exception& a)
	{
		std::cerr << a.what() << std::endl;
		throw;
	}

	window.setFramerateLimit(120);
	window.setVerticalSyncEnabled(true);
	
	ObjectReader test("trueno");
	
	VertexBuffer vao;

	vao.addVertexBuffer(test.getVertexData());
	vao.addVertexBuffer(test.getVNormalData());
	vao.addIndices(test.getVertIndices());
	
	
	Shader testshader("test");
	
	testshader.bindAttrib(0, "pos");
	testshader.bindAttrib(1, "inNormals");
	testshader.link();
	testshader.setShader();
	Events events(&window);
	
	while (window.isOpen())
	{
		events.update(&vao, &testshader);
	}
	glfwTerminate();
	return 0;
}
