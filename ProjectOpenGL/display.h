#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

class Display
{
public:
	GLFWwindow* m_window;

	Display(int width, int height, const std::string& title);
	void Clear(float R, float G, float B, float O);
	virtual ~Display();

protected: 
private:
	Display(const Display& other) {}
	void operator=(const Display& other) {}

	int screenWidth;
	int screenHeight;
};

