#include "mesh.h"
#include "obj_loader.h"
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	for(unsigned int i = 0; i < numVertices; i++)
	{
		// * ... derefrencing pointers
		model.positions.push_back(*vertices[i].getPos());
		model.texCoords.push_back(*vertices[i].getTexCoord());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

		InitMesh(model);

	//m_drawCount = numVertices;
	//m_drawCount = numIndices;

	//glGenVertexArrays(1, &m_vertexArrayObject);
	//// binding the object so everything we do effects him
	//glBindVertexArray(m_vertexArrayObject);

	//std::vector<glm::vec3> positions;
	//std::vector<glm::vec2> texCoords;
	//// reserving known ammount of data so we don't have to keep reallocating
	//positions.reserve(numVertices);
	//texCoords.reserve(numVertices);
	//   	 
	//for(unsigned int i = 0; i < numVertices; i++)
	//{
	//	// * ... derefrencing pointers
	//	positions.push_back(*vertices[i].getPos());
	//	texCoords.push_back(*vertices[i].getTexCoord());
	//}

	//glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	//// GL_ARRAY_BUFFER... interpret this buffer data as an array
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	//glBufferData(
	//	GL_ARRAY_BUFFER, 
	//	// put all of our vertex data in to our array 
	//	numVertices * sizeof(positions[0]),
	//	&positions[0],
	//	// we will not change it much
	//	GL_STATIC_DRAW
	//);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(
	//	// we have 0 atrrib to enterpert
	//	0,
	//	// we have 3 pieces of data (vec3)
	//	3,
	//	GL_FLOAT,
	//	GL_FALSE,
	//	// we don't skip any in between
	//	0,
	//	// we don't have to skip any beforehand
	//	0
	//);

	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//// With element we decleare an array that refrences data in another array
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	//// unbinding the object (setting the bind to 0)
	//glBindVertexArray(0);
}

Mesh::Mesh(const std::string & fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::InitMesh(const IndexedModel & model)
{
	m_drawCount = model.indices.size();

	glGenVertexArrays(1, &m_vertexArrayObject);
	// binding the object so everything we do effects him
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	// GL_ARRAY_BUFFER... interpret this buffer data as an array
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(
		GL_ARRAY_BUFFER,
		// put all of our vertex data in to our array 
		model.positions.size() * sizeof(model.positions[0]),
		&model.positions[0],
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

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// With element we decleare an array that refrences data in another array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	// unbinding the object (setting the bind to 0)
	glBindVertexArray(0);
}

void Mesh::Draw() 
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray(0);
}
