#pragma once
#include "SFML/Graphics.hpp"

#include "VertexBuffer.h"
#include "Shader.h"
#include "mx/mx.h"
#include "ViewCam.h"

class Events
{
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock;

	ViewCam cam;
	
	float screenW;
	float screenH;
	
	float time = 0.f;

	// Variables for handling mouse button events
	bool draggingL;
	bool draggingM;
	bool draggingR;
	
public:
	Events(sf::RenderWindow* window);
	Events(Events&) = delete;
	glm::vec2 getRelativeMousePos();
	void update(VertexBuffer* vao = nullptr, Shader* shader = nullptr);
};