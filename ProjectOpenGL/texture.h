#pragma once

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& fileName);

	void Bind(unsigned int unit);

	virtual ~Texture();

protected:
private:
	// OpenGL provides some neat utilities for copying so we could implement those in the future
	Texture(const Texture& other) {}
	void operator=(const Texture& other) {}

	// a place to store a handle to the texture
	GLuint m_texture;
};