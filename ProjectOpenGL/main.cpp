#include <iostream>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main()
{
	Display display(WIDTH, HEIGHT, "Hello World!");

	// ./ should look to current directory
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Mesh mesh2("./res/monkey3.obj");

	Transform transform;

	Camera camera(glm::vec3(0, 0, -4), 70.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);

	float counter = 0.0f;

	Vertex vertices[] = 
	{ 
		Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(-0.5, 0.5, 0.0), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(0.0, 0.0)),

		Vertex(glm::vec3(0.5, 0.5, 0.0), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(-0.5, 0.5, 0.0), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(0.0, 0.0))
	};
	unsigned int indices[] = { 0, 1, 2, 3, 4, 5};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	// Game loop
	while (!glfwWindowShouldClose(display.m_window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform.getPos().x = sinCounter;
		transform.getPos().z = cosCounter;
		transform.getRot().x = counter * 2;
		transform.getRot().y = counter * 2;
		transform.getRot().z = counter * 2;
		//transform.setScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		// Render
		// Clear the colorbuffer
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh2.Draw();

		// Swap the screen buffers
		glfwSwapBuffers(display.m_window);
		counter += 0.0007f;
	}

	return 0;
}

