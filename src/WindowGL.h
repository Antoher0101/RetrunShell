#ifndef WINDOWGL_H

#define WINDOWGL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <iostream>

#define MAX_KEYS	0x400
#define MAX_BUTTONS 0x020

#define M_WHEEL_UP 0x01
#define M_WHEEL_DOWN 0x02

class WindowGL
{

private:
	const char* m_Title;
	int m_Width, m_Height;
	GLFWwindow* m_Window;
	bool m_Closed;

	bool m_Keys[MAX_KEYS];
	bool m_MouseButtons[MAX_BUTTONS];
	double mX, mY;
	
	double m_WheelOffsetY;
	double m_WheelOffsetX; // Unused
	
	GLFWwindow* getWindow() const { return m_Window; }
	
	friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	friend static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	bool init();
	
public:
	WindowGL(const char* title, int width, int height);
	~WindowGL();
	void clear() const;
	bool closed() const;

	int getWidth()  const { return m_Width; }
	int getHeight() const { return m_Height; }
	
	bool isKeyPressed(unsigned int keycode) const;
	bool isMouseButtonPressed(unsigned int button) const;

	bool isWheelScrolled(unsigned int dir);
	
	glm::vec2 getMousePosition();

	friend class Events;
};
#endif
