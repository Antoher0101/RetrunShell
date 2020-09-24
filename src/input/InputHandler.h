#pragma once

#include "ICommand.h"

class CloseWindow : public InputCommand
{
	void execute(WindowGL* window, ViewCam* cam) override;
};
class ChangeVideoMode : public InputCommand
{
	void execute(WindowGL* window, ViewCam* cam) override;
};
class MoveForward : public InputCommand
{
	void execute(WindowGL* window, ViewCam* cam) override;
};
class MoveLeft : public InputCommand
{
	void execute(WindowGL* window, ViewCam* cam) override;
};
class MoveBack : public InputCommand
{
	void execute(WindowGL* window, ViewCam* cam) override;
};
class MoveRight : public InputCommand
{
	void execute(WindowGL* window, ViewCam* cam) override;
};
class Looking : public InputCommand
{
	void execute(WindowGL* window, ViewCam* cam) override;
};
class StopLooking : public InputCommand
{
	void execute(WindowGL* window, ViewCam* cam) override;
};
class NullAction : public InputCommand
{
	void execute(WindowGL* window, ViewCam* cam) override;
};

class InputHandler
{
	WindowGL* window_;
	ViewCam* cam_;
	// Keyboard
	InputCommand* Esc;
	InputCommand* F11;
	InputCommand* F3;
	InputCommand* W;
	InputCommand* A;
	InputCommand* S;
	InputCommand* D;

	// Mouse
	InputCommand* LeftMouseButton;
	InputCommand* LeftMouseButtonRelease;
	InputCommand* RightMouseButton;
	InputCommand* RightMouseButtonRelease;
	InputCommand* MouseWheelUp;
	InputCommand* MouseWheelDown;
public:
	InputHandler(WindowGL* window, ViewCam* cam);
	~InputHandler();
	void handleInput();

	void setKeyEsc(InputCommand* command) { Esc = command; }
	void setKeyF11(InputCommand* command) { F11 = command; }
	void setKeyF3(InputCommand* command) { F3 = command; }
	void setKeyW(InputCommand* command) { W = command; }
	void setKeyA(InputCommand* command) { A = command; }
	void setKeyS(InputCommand* command) { S = command; }
	void setKeyD(InputCommand* command) { D = command; }
};