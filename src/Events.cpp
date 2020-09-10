#include "Events.h"

Events::Events(WindowGL* win)
{
	window = win;
	glfw_window = win->getWindow();
}

void Events::update(std::vector<VertexBuffer*> vao, std::vector<Shader*> shader)
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

	// Clear OpenGL buffers
	glClearColor(0.15f, 0.15f, 0.15f, 1.f);
	glClearDepth(1.0f);
	window->clear();
	
	cam.setElapsedTime(deltaTime*100);
	cam.setFirstMousePos(window->getMousePosition());

	glViewport(0, 0, screenW, screenH);
	
	if (window->isKeyPressed(GLFW_KEY_ESCAPE)) { glfwSetWindowShouldClose(window->getWindow(), true); }
	if (window->isKeyPressed(GLFW_KEY_W)) { cam.movementCam(MOVE_FORWARD); }
	if (window->isKeyPressed(GLFW_KEY_S)) { cam.movementCam(MOVE_BACK); }
	if (window->isKeyPressed(GLFW_KEY_A)) { cam.movementCam(MOVE_LEFT); }
	if (window->isKeyPressed(GLFW_KEY_D)) { cam.movementCam(MOVE_RIGHT); }

	if (window->isWheelScrolled(M_WHEEL_UP)) x++;
	if (window->isWheelScrolled(M_WHEEL_DOWN)) x--;

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

	 // std::cout << "" << std::endl;
	
	mx::Model model;
	model.mTranslate({ 0.f,0.f,-2.f });
	model.mRotate(15.f, { 1.f, 1.f, 0.f });
	model.mRotate(0.f * clock, {0.f, 1.f, 0.f});
	model.mScale({0.045f,0.045f,0.045f});
	
	mx::View view;
	view.lookAt( cam.getCameraPos(), cam.getCameraPos() + cam.getCameraFront(), cam.getCameraUp());
	
	mx::Projection projection;
	projection.setPerspective(45.f, (float)screenW, (float)screenH, 0.01f, 100.f);
	shader[0]->setShader();

	shader[0]->setUniform("light.position", {-2.f,2.f,3.f});
	shader[0]->setUniform("viewPos", view.getPosition());

	
	glm::vec3 diffuseColor = glm::vec3{0.569f,0.118f,0.259f} * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.11f);
	shader[0]->setUniform("light.ambient", ambientColor);
	shader[0]->setUniform("light.diffuse", diffuseColor);
	shader[0]->setUniform("light.specular", { 1.0f, 1.0f, 1.0f });

	// material properties
	shader[0]->setUniform("material.ambient", { 0.0f,	0.0f,	0.0f });
	shader[0]->setUniform("material.diffuse", { 0.55f,0.55f	,0.55f });
	shader[0]->setUniform("material.specular", { 0.7f	,0.7f,	0.7f });
	shader[0]->setUniform("material.shininess", 128*0.25f);

	// Send the uniforms to shader
	shader[0]->setUniform("Model", model.getMatrix());
	shader[0]->setUniform("View", view.getMatrix());
	shader[0]->setUniform("Projection", projection.getMatrix());
	shader[0]->setUniform("iResolution", (float)screenW,(float)screenH );
	shader[0]->setUniform("iTime", clock);
	vao[0]->drawObj();


	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	shader[1]->setShader();
	glm::mat4 viewS = glm::mat4(glm::mat3(view.getMatrix()));
	shader[1]->setUniform("View", viewS);
	shader[1]->setUniform("viewPos", view.getPosition());
	shader[1]->setUniform("Projection", projection.getMatrix());
	shader[1]->setUniform("iResolution", (float)screenW, (float)screenH);
	shader[1]->setUniform("iTime", clock);
	vao[1]->drawObj(GL_TRIANGLES, GL_TEXTURE_CUBE_MAP);
	glDepthMask(GL_TRUE);
	glDisable(GL_CULL_FACE);
	
	
	if (draggingL) { cam.calculateCam(); }

	glfwSwapBuffers(glfw_window);
}
