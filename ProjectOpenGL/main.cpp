#include <iostream>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"


// Window dimensions
const GLint WIDTH = 1280, HEIGHT = 720;

// The MAIN function, from here we start the application and run the game loop
int main()
{
	Display display(800, 600, "Hello World!");
	// I am assuming that ./ does nothing in this case ? 
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");

	Vertex vertices[] = 
	{ 
		Vertex(glm::vec3(-0.5, -0.5, 0)),
		Vertex(glm::vec3(-0.5, 0.5, 0)),
		Vertex(glm::vec3(0.5, -0.5, 0)),

		Vertex(glm::vec3(0.5, 0.5, 0)),
		Vertex(glm::vec3(-0.5, 0.5, 0)),
		Vertex(glm::vec3(0.5, -0.5, 0))
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	// Game loop
	while (!glfwWindowShouldClose(display.m_window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		shader.Bind();
		mesh.Draw();

		// Swap the screen buffers
		glfwSwapBuffers(display.m_window);
	}

	return 0;
}

