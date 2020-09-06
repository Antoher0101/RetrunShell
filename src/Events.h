#ifndef EVENTS_H
#define EVENTS_H

#include "VertexBuffer.h"
#include "Shader.h"
#include "mx/mx.h"
#include "ViewCam.h"
#include "WindowGL.h"

class Events
{
	WindowGL* window;

	GLFWwindow* glfw_window;

	ViewCam cam;
	
	int screenW;
	int screenH;
	
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// Variables for handling mouse button events
	bool draggingL = false;
	bool draggingM = false;
	bool draggingR = false;

	bool wasReleased = true;
public:
	Events(WindowGL* win);
	Events(Events&) = delete;
	void update(VertexBuffer* vao = nullptr, Shader* shader = nullptr);
};

#endif
