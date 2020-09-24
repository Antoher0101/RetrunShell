#pragma once

#include "VertexBuffer.h"
#include "Shader.h"
#include "mx/mx.h"
#include "ViewCam.h"
#include "WindowGL.h"
#include "input/InputHandler.h"

class Events
{
	WindowGL* window_;
	GLFWwindow* glfw_window_;
	ViewCam cam_;
	
	int screenW;
	int screenH;
	
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

public:
	Events(WindowGL* win) : window_(win), glfw_window_(win->getWindow()) {}
	Events(Events&) = delete;
	void update(std::vector<VertexBuffer*> vao = { nullptr }, std::vector<Shader*> shader = { nullptr }, gltext::Text* text = nullptr);
};

