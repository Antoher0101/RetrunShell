#include "Events.h"
#include "Material.h"
Events::Events(WindowGL* win)
{
	window = win;
	glfw_window = win->getWindow();
}

void Events::update(std::vector<VertexBuffer*> vao, std::vector<Shader*> shader, gltext::Text* text)
{
	// OpenGL error handle
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "OpenGL Error: " << error << std::endl;
	
	// Get screen size
	glfwGetWindowSize(glfw_window, &screenW, &screenH);	
	glfwSwapInterval(1);

	gltext::Text::updateScreenSize(screenW, screenH);
	
	GLfloat clock = glfwGetTime();
	deltaTime = clock - lastFrame;
	lastFrame = clock;
	// Start events handle 
	glfwPollEvents();

	// Clear OpenGL buffers
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClearDepth(1.0f);
	
	window->clear();
	
	// it works somehow
	cam.resetMouseDelta();
	
	cam.setElapsedTime(deltaTime*100);
	cam.setFirstMousePos(window->getMousePosition());

	if (window->isKeyPressed(GLFW_KEY_ESCAPE)) { glfwSetWindowShouldClose(window->getWindow(), true); }
	if (window->isKeyPressed(GLFW_KEY_W)) { cam.movementCam(MOVE_FORWARD); }
	if (window->isKeyPressed(GLFW_KEY_S)) { cam.movementCam(MOVE_BACK); }
	if (window->isKeyPressed(GLFW_KEY_A)) { cam.movementCam(MOVE_LEFT); }
	if (window->isKeyPressed(GLFW_KEY_D)) { cam.movementCam(MOVE_RIGHT); }
	
	if (window->isWheelScrolled(M_WHEEL_UP)) x+=0.001;
	if (window->isWheelScrolled(M_WHEEL_DOWN)) if (x-0.001 > 0) { x -= 0.001; }

	if(window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		draggingL = true;
		if (!wasReleased) {
			 cam.setMouseLastPos(window->getMousePosition());
		}
	} else {
		glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		draggingL = false;
		wasReleased = true;
	}
	
	cam.setMotionSpeed(x);
	 // std::cout << "" << std::endl;

	text->setPos(AT_CENTER);
	text->RenderText("T h e  Q u i c k  B r o w n  F o x", shader[0]);
	text->setPos(AT_LEFT | AT_TOP);
	text->RenderText("SHIFT BUG", shader[0]);
	
	
	
	//text->setPos(AT_CENTER);
	//text->RenderText("N I N J A   N A R U T O", shader[0]);
	
	if (draggingL) { cam.calculateCam(); }
	glfwSwapBuffers(glfw_window);
}
