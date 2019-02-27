#include "mesh.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	m_drawCount = numVertices;

	glGenVertexArrays(1, &m_vertexArrayObject);
	// binding the object so everything we do effects him
	glBindVertexArray(m_vertexArrayObject);
	   	 
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	// GL_ARRAY_BUFFER... interpret this buffer data as an array
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(
		GL_ARRAY_BUFFER, 
		// put all of our vertex data in to our array 
		numVertices * sizeof(vertices[0]),
		vertices,
		// we will not change it much
		GL_STATIC_DRAW
	);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		// we have 0 atrrib to enterpert
		0,
		// we have 3 pieces of data (vec3)
		3,
		GL_FLOAT,
		GL_FALSE,
		// we don't skip any in between
		0,
		// we don't have to skip any beforehand
		0
	);

	// unbinding the object (setting the bind to 0)
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() 
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray(0);
}
