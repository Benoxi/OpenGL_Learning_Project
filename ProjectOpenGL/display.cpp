#include "display.h"


Display::Display(int width, int height, const std::string& title)
{
	// Initializing GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	glfwGetFramebufferSize(m_window, &screenWidth, &screenHeight);

	if (nullptr == m_window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		std::cout << "return EXIT_FAILURE" << std::endl;
	}

	glfwMakeContextCurrent(m_window);

	// Initializing GLEW
	GLenum status = glewInit();

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (status != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		std::cout << "return EXIT_FAILURE" << std::endl;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
}

void Display::Clear(float R, float G, float B, float O)
{
	glClearColor(R, G, B, O);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Display::~Display()
{
	//std::cout << "Destructor!" << std::endl;
	glfwDestroyWindow(m_window);
	// Should deinitialize everything m_window related
	glfwTerminate();
}

