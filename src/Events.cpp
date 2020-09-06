#include "Events.h"

Events::Events(sf::RenderWindow* win)
{
	screenW = static_cast<float>(win->getSize().x);
	screenH = static_cast<float>(win->getSize().y);
	window = win;
}

glm::vec2 Events::getRelativeMousePos()
{
	return { window->getPosition().x + screenW/2, window->getPosition().y + screenH/2 };
}

void Events::update(VertexBuffer* vao, Shader* shader)
{
	float etime = clock.getElapsedTime().asSeconds();
	
	clock.restart();
	time += etime;
	cam.setElapsedTime(etime*100);
	cam.setMousePos({ (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y });
	
	while (window->pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window->close(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { cam.movementCam(MOVE_FORWARD); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { cam.movementCam(MOVE_BACK); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { cam.movementCam(MOVE_LEFT); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { cam.movementCam(MOVE_RIGHT); }
		// Event handler
		switch (event.type) 
		{
		case sf::Event::Resized:
		{
			screenW = (float)window->getSize().x;
			screenH = (float)window->getSize().y;
			window->setActive(true);
			glViewport(0, 0, event.size.width, event.size.height);
			window->setActive(false);
			break;
		}
		case sf::Event::Closed: window->close(); break;
		case sf::Event::KeyPressed: {
			
			break;
		}
		case sf::Event::MouseWheelScrolled:
		{
			if (event.mouseWheelScroll.delta < 0);
			if (event.mouseWheelScroll.delta > 0);
			break;
		}
		case sf::Event::MouseButtonPressed: {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				window->setMouseCursorVisible(false);
				draggingL = true;
				cam.setMouseLastPos({ (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y });
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
				window->setMouseCursorVisible(false);
				draggingM = true;
				cam.setMouseLastPos({ (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y });
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				window->setMouseCursorVisible(false);
				draggingR = true;
				cam.setMouseLastPos({ (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y });
			}
			break;
		}
		case sf::Event::MouseButtonReleased: {
			if (event.mouseButton.button == sf::Mouse::Left) { window->setMouseCursorVisible(true); draggingL = false; }
			if (event.mouseButton.button == sf::Mouse::Middle) { window->setMouseCursorVisible(true); draggingM = false; }
			if (event.mouseButton.button == sf::Mouse::Right) { window->setMouseCursorVisible(true); draggingR = false; }
			break;
		}
		default: break;
		}
	}
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	mx::Model model;
	model.mTranslate({ 0.f,0.f,-2.f });
	model.mRotate(15.f, { 1.f, 1.f, 0.f });
	model.mRotate(90.f*time, {0.f, 1.f, 0.f});
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
	shader->setUniform("iTime", time);
	
	vao->drawObj();
	
	if (draggingL || draggingM || draggingR) {
		cam.calculateCam();
	}
	window->display();
}
