#include <iostream>

#include "Events.h"
#include "Shader.h"
#include "VertexBuffer.h"

#include "WindowGL.h"

#include "ModelReader.h"
#include "Mesh.h"

#include "Text.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

// TODO: https://habr.com/ru/post/347354/
// TODO: UniformBuffer (View, Projection)
// TODO: Display text and current speed
// TODO: Move key handle to WindowGL

int main(int argc, char* argv[])
{	
	WindowGL window("GLFW", WIDTH, HEIGHT);

	VertexBuffer textBuffer;
	gltext::Text txt(textBuffer);
	txt.init("consola.ttf", 32);
	txt.genGlyphList();
	textBuffer.addTextBuffer();
	
	Shader textShader("text");
	textShader.bindAttrib(0, "vertex");
	textShader.link();
	
	Events events(&window);
	while (!window.closed())
	{
		events.update({ &textBuffer }, { &textShader }, &txt);
	}
	return 0;
}