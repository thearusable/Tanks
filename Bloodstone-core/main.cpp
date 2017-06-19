#include <iostream>

#include "graphics/Window.h"

#include "Engine.h"

using namespace bs::graphics;

int main() {

	int i = 5;
	float f = 3.0f;

	BS_LOG << "Testing: " << i << "\n" << f << std::endl; // compatible with iostream syntax
	BS_LOG << "The auto-flush actually discourages usage of endl";

	BS_WARNING << "Warning message"; // no final endl required because of auto-flushing

	for (int j = 0; j < 100; ++j) {
		if (j % 30)
			BS_LOG << "Normal message should look normal";
		else
			BS_ERROR << "Error messages should be super noticable";

		if (j % 50 == 0)
			BS_DEBUG << "Debug messages should be also quick to spot";
	}

	/*
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
	*/
	return 0;
}