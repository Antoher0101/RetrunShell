#include <iostream>

#include "Events.h"
#include "Shader.h"
#include "VertexBuffer.h"

#include "WindowGL.h"

#include "ObjectReader.h"
#include "ModelReader.h"
#include "Mesh.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

// TODO: move load texture function to ModelReader as static func
// TODO: https://habr.com/ru/post/347354/

int main(int argc, char* argv[])
{
	
	WindowGL window("GLFW", WIDTH, HEIGHT);

	ModelReader skycube("cube.obj");
	VertexBuffer skyboxBuf;

    skyboxBuf.addVertexBuffer(skycube.getMeshes()[0].getVertexPos());
    skyboxBuf.addCubeMapBuffer({"negx.jpg",
                                        "posx.jpg",
                                        "posy.jpg",
                                        "negy.jpg",
                                        "negz.jpg",
                                        "posz.jpg"});
	skyboxBuf.addIndices(skycube.getMeshes()[0].getIndeces());
    Shader skybox("skybox");
    skybox.bindAttrib(0, "pos");
	skybox.bindAttrib(1, "texCoord");
	skybox.link();
	
	VertexBuffer vao;
	ModelReader model("TruenoT.obj");
	
	vao.addVertexBuffer(model.getMeshes()[0].getVertexPos());
	vao.addVertexBuffer(model.getMeshes()[0].getVertexNormals());
	vao.addVertexBuffer(model.getMeshes()[0].getTexCoords());
	vao.addIndices(model.getMeshes()[0].getIndeces());
	vao.addTextureBuffer("tex.jpg");
	
	Shader trueno("test");
	trueno.bindAttrib(0, "pos");
	trueno.bindAttrib(1, "normal");
	trueno.bindAttrib(2, "texCoord");
	trueno.link();
	
	Events events(&window);
	while (!window.closed()) { events.update({ &vao, &skyboxBuf }, { &trueno, &skybox }); }

	return 0;
}
