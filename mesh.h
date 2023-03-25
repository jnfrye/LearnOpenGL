#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mesh
{
	unsigned int ElementsSize;
	unsigned int* Elements;

	unsigned int VerticesSize;
	GLfloat* Vertices;

	unsigned int VertexArrayObj;
	unsigned int VertexBufferObj;
	unsigned int ElementBufferObj;

public:
	Mesh(unsigned  int verticesSize, GLfloat vertices[], unsigned int elementsSize, unsigned int elements[]);
	void Initialize();
	void CleanUp();
	void Draw();
};