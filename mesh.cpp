#include "mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Mesh::Mesh(unsigned int verticesSize, GLfloat vertices[], unsigned int elementsSize, unsigned int elements[])
	: VerticesSize{ verticesSize }, Vertices { vertices }, ElementsSize{ elementsSize }, Elements{ elements },
	VertexArrayObj{ }, VertexBufferObj{ }, ElementBufferObj{ }
{ }

void Mesh::Initialize()
{
	// Bind the VAO to store everything in
	glGenVertexArrays(1, &VertexArrayObj);

	glBindVertexArray(VertexArrayObj);

	// Set up the vertex buffer
	glGenBuffers(1, &VertexBufferObj);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObj); // Bind the buffer as the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, VerticesSize, Vertices, GL_STATIC_DRAW); // Stuff the vertex data into the buffer

	// Set up the element buffer
	glGenBuffers(1, &ElementBufferObj);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementsSize, Elements, GL_STATIC_DRAW);

	// Tell OpenGL how our attribute is laid out in the array
	unsigned int location = 0;
	unsigned int coordsPerVertex = 3;
	unsigned int stride = coordsPerVertex * sizeof(float);
	unsigned int offset = 0;
	glVertexAttribPointer(location, coordsPerVertex, GL_FLOAT, GL_FALSE, stride, (void*)offset);

	// Must also enable it!
	glEnableVertexAttribArray(location);
}

void Mesh::CleanUp()
{
	glDeleteVertexArrays(1, &VertexArrayObj);
	glDeleteBuffers(1, &VertexBufferObj);
	glDeleteBuffers(1, &ElementBufferObj);
}

void Mesh::Draw()
{
	glBindVertexArray(VertexArrayObj);
	glDrawElements(GL_TRIANGLES, ElementsSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
