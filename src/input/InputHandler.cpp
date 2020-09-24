#include "InputHandler.h"
#include "../WindowGL.h"
#include  "../ViewCam.h"

InputHandler::InputHandler(WindowGL* window, ViewCam* cam)
{
	window_ = window;
	cam_ = cam;
	
	Esc = new CloseWindow;
	F11 = new ChangeVideoMode;
	W = new MoveForward;
	A = new MoveLeft;
	S = new MoveBack;
	D = new MoveRight;
	LeftMouseButton = new Looking;
	LeftMouseButtonRelease = new StopLooking;
	RightMouseButton = new NullAction;
	RightMouseButtonRelease = new NullAction;
	MouseWheelUp = new NullAction;
	MouseWheelDown = new NullAction;
}

void InputHandler::handleInput()
{
	if (window_->isKeyPressed(GLFW_KEY_ESCAPE)) {
		Esc->execute(window_, cam_);
	}
	if (window_->isKeyPressed(GLFW_KEY_F11)) {
		F11->execute(window_, cam_);
	}
	if (window_->isKeyPressed(GLFW_KEY_F3)) {
		F3->execute(window_, cam_);
	}
	if (window_->isKeyPressed(GLFW_KEY_W)) {
		W->execute(window_, cam_);
	}
	if (window_->isKeyPressed(GLFW_KEY_A)) {
		A->execute(window_, cam_);
	}
	if (window_->isKeyPressed(GLFW_KEY_S)) {
		S->execute(window_, cam_);
	}
	if (window_->isKeyPressed(GLFW_KEY_D)) {
		D->execute(window_, cam_);
	}
	if (window_->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		LeftMouseButton->execute(window_, cam_);
	}
	if (!window_->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		LeftMouseButtonRelease->execute(window_, cam_);
	}
}

void CloseWindow::execute(WindowGL* window, ViewCam* cam)
{
	glfwSetWindowShouldClose(window->getWindow(), true);
}

void ChangeVideoMode::execute(WindowGL* window, ViewCam* cam)
{
	window->changeFullscreen();
}

void MoveForward::execute(WindowGL* window, ViewCam* cam)
{
	cam->movementCam(MOVE_FORWARD);
}

void MoveLeft::execute(WindowGL* window, ViewCam* cam)
{
	cam->movementCam(MOVE_LEFT);
}

void MoveBack::execute(WindowGL* window, ViewCam* cam)
{
	cam->movementCam(MOVE_BACK);
}

void MoveRight::execute(WindowGL* window, ViewCam* cam)
{
	cam->movementCam(MOVE_RIGHT);
}

void Looking::execute(WindowGL* window, ViewCam* cam)
{
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	window->setMouseLButtonState(true);
	if (!window->getMouseLButtonState()) {
		cam->setMouseLastPos(window->getMousePosition());
	}
}
void StopLooking::execute(WindowGL* window, ViewCam* cam)
{
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	window->setMouseLButtonState(false);
}

void NullAction::execute(WindowGL* window, ViewCam* cam)
{
}

InputHandler::~InputHandler()
{
	delete Esc;
	delete F11;
	delete F3;
	delete W;
	delete A;
	delete S;
	delete D;
	delete LeftMouseButton;
	delete LeftMouseButtonRelease;
	delete RightMouseButton;
	delete RightMouseButtonRelease;
	delete MouseWheelUp;
	delete MouseWheelDown;
}