#include <GLFW\glfw3.h>
#include <iostream>

#include "src/graphics/Window.h"

using namespace bs::graphics;

int main() {

	Window window("Bloodstone", 800, 600);
	glClearColor(0.2f, 0.2f, 0.8f, 1.0f);

	while (!window.closed()) {
		window.clear();
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		window.update();
	}

	return 0;
}