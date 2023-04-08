#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct VertAttr
{
	unsigned int Count;
};

class Mesh
{
	unsigned int ElemsCount;
	unsigned int* Elems;

	unsigned int VertsCount;
	GLfloat* Verts;

	unsigned int AttrsCount;
	VertAttr* Attrs;

	unsigned int VertArrayObj;
	unsigned int VertBufferObj;
	unsigned int ElemBufferObj;

public:
	Mesh(
		unsigned int vertsCount, GLfloat* verts,
		unsigned int elemsCount, unsigned int* elems,
		unsigned int attrsCount, VertAttr* attrs
	);
	void Initialize();
	void CleanUp();
	void Draw();
};