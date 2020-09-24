#pragma once

class ViewCam;
class WindowGL;

class InputCommand
{
public:
	virtual ~InputCommand() {}
	virtual void execute(WindowGL* window, ViewCam* cam) = 0;
};

