#include <iostream>

#include "Events.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "ObjectReader.h"
#include "WindowGL.h"


const int WIDTH = 1280;
const int HEIGHT = 720;



int main(int argc, char* argv[])
{
	WindowGL window("GLFW", WIDTH,HEIGHT);
	
	ObjectReader test("trueno");
	
	VertexBuffer vao;

	vao.addVertexBuffer(test.getVertexData());
	vao.addVertexBuffer(test.getVNormalData());
	vao.addIndices(test.getVertIndices());
	
	
	Shader testshader("test");
	
	testshader.bindAttrib(0, "pos");
	testshader.bindAttrib(1, "inNormals");
	testshader.link();
	testshader.setShader();
	Events events(&window);
	
	while (!window.closed())
	{
		events.update(&vao, &testshader);
	}
	
	return 0;
}
