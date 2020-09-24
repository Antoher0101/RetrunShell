#include "Events.h"
#include "Material.h"

void Events::update(std::vector<VertexBuffer*> vao, std::vector<Shader*> shader, gltext::Text* text)
{
	// OpenGL error handle
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "OpenGL Error: " << error << std::endl;
	
	// Get screen size
	glfwGetWindowSize(glfw_window_, &screenW, &screenH);	
	glfwSwapInterval(0);

	gltext::Text::updateScreenSize(screenW, screenH);
	
	GLfloat clock = glfwGetTime();
	deltaTime = clock - lastFrame;
	lastFrame = clock;
	// Start events handle 
	glfwPollEvents();

	
	// Clear OpenGL buffers
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClearDepth(1.0);
	
	window_->clear();
	
	// it works somehow
	cam_.resetMouseDelta();
	
	cam_.setElapsedTime(deltaTime*100);
	cam_.setFirstMousePos(window_->getMousePosition());
	
	InputHandler input_handler(window_,&cam_);
	input_handler.handleInput();

	 // std::cout << "" << std::endl;
	
	

	mx::Model model;
	model.mTranslate({ 0.f,0.f,-2.f });
	model.mRotate(15.f, { 1.f, 1.f, 0.f });
	model.mRotate(0.f * clock, { 0.f, 1.f, 0.f });
	model.mScale({ 0.045f,0.045f,0.045f });
	mx::View view;
	view.lookAt(cam_.getCameraPos(), cam_.getCameraPos() + cam_.getCameraFront(), cam_.getCameraUp());

	mx::Projection projection;
	projection.setPerspective(45.f, (float)screenW, (float)screenH, 0.01f, 100.f);
	shader[2]->setShader();

	shader[2]->setUniform("light.position", { 0.f,0.f,0.f });
	shader[2]->setUniform("viewPos", cam_.getCameraUp() /*view.getPosition()*/);

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
	
	text->setColor(1.f, 0.f, 0.5f);
	//text->setOutline();
	text->setOutlineColor(0.f, 0.f, 1.f);
	text->setPos(150,150);
	text->RenderText(shader[0], "FUCK THIS:    ", std::to_string(static_cast<unsigned short>(10-clock)));
	
	if (window_->getMouseLButtonState()) { cam_.calculateCam(); }
	glfwSwapBuffers(glfw_window_);
}