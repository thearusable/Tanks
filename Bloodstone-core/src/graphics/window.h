#ifndef WINDOW_H
#define WINDOW_H

#pragma once
#include <string>
#include <iostream>
#include <GLFW/glfw3.h>

namespace bs { namespace graphics {

class Window
{
	std::string m_Name;
	int m_Width, m_Height;
	GLFWwindow* m_Window;

	bool init();

public:
	Window(const std::string& name, const int& width, const int& height);
	~Window();

	void update();
	bool closed() const;
	void clear() const;

	inline int getWidth() { return m_Width; }
	inline int getHeight() { return m_Height; }
};

} }
#endif