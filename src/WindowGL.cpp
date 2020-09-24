#include "WindowGL.h"

// Not WindowGL::methods // Recall that the WindowUserPointer is our current context and our current window
void window_resize(GLFWwindow* window, int width, int height)
{
	
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)	// We can only access public things and friends.
{
	WindowGL* win = (WindowGL*)glfwGetWindowUserPointer(window);						// GLFW's Pointer casted to and pointed at OUR WINDOW CLASS
	win->m_Keys[key] = action != GLFW_RELEASE;										// Map of the window's keypress buffer
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	WindowGL* win = (WindowGL*)glfwGetWindowUserPointer(window);						// Logical
	win->m_MouseButtons[button] = action != GLFW_RELEASE;							// Map of the window's MousePress buffer
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	WindowGL* win = (WindowGL*)glfwGetWindowUserPointer(window);
	win->mX = xpos;
	win->mY = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	WindowGL* win = (WindowGL*)glfwGetWindowUserPointer(window);
	win->m_WheelOffsetY = yoffset;
}

WindowGL::WindowGL(const char* title, int width, int height)
{
	m_Title = title;
	m_Width = width;
	m_Height = height;
	if (!init())			// Error handle
		glfwTerminate();

	for (int i = 0; i < MAX_KEYS; i++)
		m_Keys[i] = false;
	for (int i = 0; i < MAX_BUTTONS; i++)
		m_MouseButtons[i] = false;

	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
WindowGL::~WindowGL()
{
	glfwTerminate();
}
bool WindowGL::init()
{
	// Initialize glfw
	try  
	{
		if (!glfwInit()) { throw std::runtime_error("Could not initialize GLFW"); }
		
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);		// Returns a pointer

	if (!m_Window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return false;
	}

	// Initialize glfw contexts & callbacks
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);						// This ties a pointer (m_Window) to GL window.

	glfwSetWindowSizeCallback(m_Window, window_resize);				// Set window resize callback
	glfwSetKeyCallback(m_Window, key_callback);						// Set Key callback
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);	// Set Mouse Callback
	glfwSetCursorPosCallback(m_Window, cursor_position_callback);	// Set Cursor Pos Callback
	glfwSetScrollCallback(m_Window, scroll_callback);				// Set scroll Callback
	glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback); 

	// GLEW initialization
	try
	{
		if (glewInit() != GLEW_OK)
			throw std::runtime_error("Could not initialize GLEW");
	}
	catch (const std::exception& a)
	{
		std::cerr << a.what() << std::endl;
		throw;
	}

	//std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

	return true;
}
bool WindowGL::isKeyPressed(unsigned int keycode) const
{
	if (keycode >= MAX_KEYS)
		return false;
	return m_Keys[keycode];
}

bool WindowGL::isMouseButtonPressed(unsigned int button) const
{
	if (button >= MAX_BUTTONS)
		return false;
	return m_MouseButtons[button];
}

bool WindowGL::isWheelScrolled(unsigned int dir)
{
	if (dir == M_WHEEL_UP && m_WheelOffsetY > 0)
	{
		m_WheelOffsetY = 0;
		return true;
	}
	if (dir == M_WHEEL_DOWN && m_WheelOffsetY < 0)
	{
		m_WheelOffsetY = 0;
		return true;
	}
	return false;
}


glm::vec2 WindowGL::getMousePosition()
{
	glfwGetCursorPos(m_Window, &mX, &mY);
	return { mX,mY };
}

void WindowGL::setMouseLButtonState(bool state)
{
	leftMouseButtonState = state;
}

void WindowGL::setMouseRButtonState(bool state)
{
	rightMouseButtonState = state;
}

bool WindowGL::getMouseLButtonState()
{
	return leftMouseButtonState;
}

bool WindowGL::getMouseRButtonState()
{
	return rightMouseButtonState;
}

void WindowGL::changeFullscreen()
{
	if (fullscreen == true)
	{
		glfwSetWindowMonitor(m_Window, NULL, m_Width / 4, m_Height / 4, 1280, 720, GLFW_DONT_CARE);
		fullscreen = false;
	}
	else
	{
		glfwSetWindowMonitor(m_Window, glfwGetPrimaryMonitor(), 0, 0, 1980, 1080, GLFW_DONT_CARE);
		fullscreen = true;
	}
}

void WindowGL::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool WindowGL::closed() const
{
	return glfwWindowShouldClose(m_Window) == 1;			// Because its a bool.....raises warning, closes window
}


