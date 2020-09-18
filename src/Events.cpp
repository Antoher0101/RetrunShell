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
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClearDepth(1.0);
	
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
	
	

	mx::Model model;
	model.mTranslate({ 0.f,0.f,-2.f });
	model.mRotate(15.f, { 1.f, 1.f, 0.f });
	model.mRotate(0.f * clock, { 0.f, 1.f, 0.f });
	model.mScale({ 0.045f,0.045f,0.045f });
	mx::View view;
	view.lookAt(cam.getCameraPos(), cam.getCameraPos() + cam.getCameraFront(), cam.getCameraUp());

	mx::Projection projection;
	projection.setPerspective(45.f, (float)screenW, (float)screenH, 0.01f, 100.f);
	shader[2]->setShader();

	shader[2]->setUniform("light.position", { 0.f,0.f,0.f });
	shader[2]->setUniform("viewPos", cam.getCameraUp() /*view.getPosition()*/);

	shader[2]->setMaterial(Material::silver());

	glm::vec3 diffuseColor = glm::vec3{ 0.569f,0.118f,0.259f } *glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.11f);
	shader[2]->setUniform("light.ambient", ambientColor);
	shader[2]->setUniform("light.diffuse", diffuseColor);
	shader[2]->setUniform("light.specular", { 1.0f, 1.0f, 1.0f });

	// Send the uniforms to shader
	shader[2]->setUniform("Model", model.getMatrix());
	shader[2]->setUniform("View", view.getMatrix());
	shader[2]->setUniform("Projection", projection.getMatrix());
	shader[2]->setUniform("iResolution", (float)screenW, (float)screenH);
	shader[2]->setUniform("iTime", clock);
	vao[2]->drawObj();

	// Skybox
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
	vao[1]->drawObj(GL_TRIANGLES, 1, GL_TEXTURE_CUBE_MAP);
	glDepthMask(GL_TRUE);
	glDisable(GL_CULL_FACE);
	
	text->setColor(0.f, 1.f, 1.f);
	text->setPos(AT_CENTER);
	text->RenderText("T h e  Q u i c k  B r o w n  F o x", shader[0]);
	
	if (draggingL) { cam.calculateCam(); }
	glfwSwapBuffers(glfw_window);
}
