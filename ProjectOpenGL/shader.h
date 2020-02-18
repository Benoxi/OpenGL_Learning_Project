#pragma once
#include <string>
#include <GL/glew.h>

#include "transform.h"
#include "camera.h"

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform, const Camera& camera);

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

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint m_program = NULL;
	GLuint m_shaders[NUM_SHADERS] = {};
	GLuint m_uniforms[NUM_UNIFORMS] = {};
};