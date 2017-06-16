#include "window.h"

namespace bs {
	namespace graphics {


void resize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


Window::Window(const std::string& name, const int& width, const int& height)
	:m_Name(name)
	,m_Width(width)
	,m_Height(height)
{
	if (!init()) {
		glfwTerminate();
	}

}


Window::~Window()
{
	glfwTerminate();
}

void Window::update() {
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}



bool Window::init() {
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return false;
	}
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), nullptr, nullptr);
	if (!m_Window) {
		std::cout << "Failed to create Window!" << std::endl;
		return false;
	}
	
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowSizeCallback(m_Window, resize);

	if (glewInit() != GLEW_OK) {
		std::cout << "Initializing GLEW failed!" << std::endl;
		return false;
	}
	
	std::cout << "OpenGL: " << glGetString(GL_VERSION);
	return true;
}

bool Window::closed() const{
	return glfwWindowShouldClose(m_Window) == 1;
}

void Window::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



	}
}