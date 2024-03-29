#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_foward = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 getViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_foward, m_up);
	}

protected:
private:
	Camera(const Camera& other) {}
	void operator=(const Camera& other) {}

	glm::mat4 m_perspective = glm::mat4();
	glm::vec3 m_position = glm::vec3();
	glm::vec3 m_foward = glm::vec3();
	glm::vec3 m_up = glm::vec3();

};