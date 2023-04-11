#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

struct VertAttr
{
	unsigned int Count;
};

class Mesh
{
	std::vector<GLfloat> Verts;
	std::vector<unsigned int> Elems;
	std::vector<VertAttr> Attrs;

	unsigned int VertBufferObj;
	unsigned int ElemBufferObj;
	unsigned int VertArrayObj;

public:
	Mesh(
		std::vector<GLfloat>& verts,
		std::vector<unsigned int>& elems,
		std::vector<VertAttr>& attrs
	);
	void Initialize();
	void CleanUp();
	void Draw();
};