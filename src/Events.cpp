#include "Events.h"

Events::Events(WindowGL* win)
{
	window = win;
	glfw_window = win->getWindow();
}

void Events::update(VertexBuffer* vao, Shader* shader)
{
	// OpenGL error handle
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "OpenGL Error: " << error << std::endl;
	
	// Get screen size
	glfwGetWindowSize(glfw_window, &screenW, &screenH);
	
	glfwSwapInterval(0);
	
	GLfloat clock = glfwGetTime();
	deltaTime = clock - lastFrame;
	lastFrame = clock;

	// Start events handle 
	glfwPollEvents();

	glfwSwapBuffers(glfw_window);

	// Clear OpenGL buffers
	glClearColor(1.f, 1.f, 1.f, 1.f);
	window->clear();
	
	cam.setElapsedTime(deltaTime*100);
	cam.setFirstMousePos(window->getMousePosition());

	glViewport(0, 0, screenW, screenH);
	
	if (window->isKeyPressed(GLFW_KEY_ESCAPE)) { glfwSetWindowShouldClose(window->getWindow(), true); }
	if (window->isKeyPressed(GLFW_KEY_W)) { cam.movementCam(MOVE_FORWARD); }
	if (window->isKeyPressed(GLFW_KEY_S)) { cam.movementCam(MOVE_BACK); }
	if (window->isKeyPressed(GLFW_KEY_A)) { cam.movementCam(MOVE_LEFT); }
	if (window->isKeyPressed(GLFW_KEY_D)) { cam.movementCam(MOVE_RIGHT); }

	if (window->isWheelScrolled(M_WHEEL_UP)) std::cout << "Up!\n";
	if (window->isWheelScrolled(M_WHEEL_DOWN)) std::cout << "Down\n";

	// TODO: try to set mouse in center of screen to fix bug
	if(window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		draggingL = true;
		if (!wasReleased) cam.setMouseLastPos(window->getMousePosition());
	} else {
		glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		draggingL = false;
		wasReleased = true;
	}

	 // std::cout << "" << std::endl;
	
	mx::Model model;
	model.mTranslate({ 0.f,0.f,-2.f });
	model.mRotate(15.f, { 1.f, 1.f, 0.f });
	model.mRotate(90.f* clock, {0.f, 1.f, 0.f});
	model.mScale({0.045f,0.045f,0.045f});
	
	mx::View view;
	view.lookAt( cam.getCameraPos(), cam.getCameraPos() + cam.getCameraFront(), cam.getCameraUp());
	
	mx::Projection projection;
	projection.setPerspective(45.f, screenW, screenH, 0.01f, 1000.f);
	
	// Send the uniforms to shader
	shader->setUniform("Model", model.getMatrix());
	shader->setUniform("View", view.getMatrix());
	shader->setUniform("Projection", projection.getMatrix());
	shader->setUniform("iResolution", screenW,screenH );
	shader->setUniform("iTime", clock);
	
	vao->drawObj();
	
	if (draggingL || draggingM || draggingR) {
		cam.calculateCam();
	}
}
