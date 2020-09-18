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
	
	ModelReader skycube("cube.obj");
	VertexBuffer skyboxBuf;
	skyboxBuf.addVertexBuffer(skycube.getMeshes()[0].getVertexPos());
	skyboxBuf.addCubeMapBuffer({ "negx.jpg",
	"posx.jpg",
	"posy.jpg",
	"negy.jpg",
	"negz.jpg",
	"posz.jpg" });
	skyboxBuf.addIndices(skycube.getMeshes()[0].getIndeces());
	Shader skybox("skybox");
	skybox.bindAttrib(0, "pos");
	skybox.bindAttrib(1, "texCoord");
	skybox.link();
	
	VertexBuffer modelbuf;
	ModelReader model("TruenoT.obj");
	modelbuf.addVertexBuffer(model.getMeshes()[0].getVertexPos());
	modelbuf.addVertexBuffer(model.getMeshes()[0].getVertexNormals());
	modelbuf.addVertexBuffer(model.getMeshes()[0].getTexCoords());
	modelbuf.addIndices(model.getMeshes()[0].getIndeces());
	modelbuf.addTextureBuffer("tex.jpg");
	Shader trueno("test");
	trueno.bindAttrib(0, "pos");
	trueno.bindAttrib(1, "normal");
	trueno.bindAttrib(2, "texCoord");
	trueno.link();
	
	VertexBuffer textBuffer;
	textBuffer.addTextBuffer();
	gltext::Text txt(textBuffer);
	txt.init("lucon.ttf", 52);
	txt.genGlyphList();
	Shader textShader("text");
	textShader.link();
	
	Events events(&window);
	while (!window.closed())
	{
		events.update({ &textBuffer, &skyboxBuf, &modelbuf }, { &textShader, &skybox, &trueno }, &txt);
	}
	return 0;
}