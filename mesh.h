#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct VertAttribute
{
	unsigned int Count;
};

class Mesh
{
	unsigned int ElementsCount;
	unsigned int* Elements;

	unsigned int VerticesCount;
	GLfloat* Vertices;

	unsigned int VertAttributesCount;
	VertAttribute* VertAttributes;

	unsigned int VertexArrayObj;
	unsigned int VertexBufferObj;
	unsigned int ElementBufferObj;

public:
	Mesh(
		unsigned int vertsCount, GLfloat* verts,
		unsigned int elemsCount, unsigned int* elems,
		unsigned int attrsCount, VertAttribute* attrs
	);
	void Initialize();
	void CleanUp();
	void Draw();
};