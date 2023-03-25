#include "mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void BufferVertexData(unsigned int vertexArraySize, GLfloat vertexArray[], unsigned int elementArraySize, unsigned int elementArray[], unsigned int& vao, unsigned int& vbo, unsigned int& ebo)
{
	// Bind the VAO to store everything in
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	// Set up the vertex buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind the buffer as the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, vertexArraySize, vertexArray, GL_STATIC_DRAW); // Stuff the vertex data into the buffer

	// Set up the element buffer
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementArraySize, elementArray, GL_STATIC_DRAW);

	// Tell OpenGL how our attribute is laid out in the array
	unsigned int location = 0;
	unsigned int coordsPerVertex = 3;
	unsigned int stride = coordsPerVertex * sizeof(float);
	unsigned int offset = 0;
	glVertexAttribPointer(location, coordsPerVertex, GL_FLOAT, GL_FALSE, stride, (void*)offset);

	// Must also enable it!
	glEnableVertexAttribArray(location);
}