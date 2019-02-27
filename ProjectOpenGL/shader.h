#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();

	virtual ~Shader();

protected:
private:
	// if we want to deal with geometry shaders we should set this to 3
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other) {}
	GLuint CreateShader(const std::string& text, GLenum shaderType);
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};