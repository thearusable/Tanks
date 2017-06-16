#include <iostream>

#include "graphics/Window.h"

using namespace bs::graphics;

int main() {

	Window window("Bloodstone", 800, 600);
	glClearColor(0.2f, 0.2f, 0.8f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	while (!window.closed()) {
		window.clear();
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
		window.update();
	}

	return 0;
}