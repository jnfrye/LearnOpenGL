#include "mesh_factory.h"
#include <vector>

Mesh MeshFactory::CreateTriangle()
{
	std::vector<GLfloat> verts
	{	// X   // Y   // Z  
		-1.0f,  1.0f,  0.0f,
		-0.8f,  0.0f,  0.0f,
		-1.0f, -1.0f,  0.0f,
	};

	std::vector<unsigned int> elems
	{
		0, 1, 2
	};

	std::vector<VertAttr> attrs
	{
		VertAttr{3},
	};

	return { verts, elems, attrs };
}

Mesh MeshFactory::CreateParallelogram()
{
	std::vector<GLfloat> verts
	{	// X   // Y   // Z 	// R  // G  // B
		-0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f,
		 0.0f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f,
	};

	std::vector<unsigned int> elems
	{
		1, 2, 3,
		0, 2, 1
	};

	std::vector<VertAttr> attrs
	{
		VertAttr{3},
		VertAttr{3},
	};

	return { verts, elems, attrs };
}