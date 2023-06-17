#include "mesh_factory.h"
#include <vector>

Mesh MeshFactory::CreateTriangle()
{
	std::vector<GLfloat> verts
	{	// X   // Y   // Z  	 // phase
		-1.0f,  0.0f,  0.0f,	 0.00000f,
		 0.0f,  0.0f,  0.0f,	 0.33333f,
		-0.5f,  1.0f,  0.0f,	 0.66667f,
	};

	std::vector<unsigned int> elems
	{
		0, 1, 2
	};

	std::vector<VertAttr> attrs
	{
		VertAttr{3},
		VertAttr{1},
	};

	return { verts, elems, attrs };
}

Mesh MeshFactory::CreateParallelogram()
{
	std::vector<GLfloat> verts
	{	// X    // Y   // Z 	// R  // G  // B
		-0.50f, -1.0f, 0.0f,	1.0f, 1.0f, 1.0f,
		 0.50f, -1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
		 0.00f,  0.0f, 0.0f,	0.0f, 1.0f, 0.0f,
		 1.00f,  0.0f, 0.0f,	0.0f, 0.0f, 1.0f,
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

Mesh MeshFactory::CreateSquare()
{
	std::vector<GLfloat> verts
	{	  // X   // Y   // Z 	// S  // T
		  0.1f,  0.1f,  0.0f,	0.0f, 0.0f,
		  0.9f,  0.1f,  0.0f,	1.0f, 0.0f,
		  0.9f,  0.9f,  0.0f,	1.0f, 1.0f,
		  0.1f,  0.9f,  0.0f,	0.0f, 1.0f,
	};

	std::vector<unsigned int> elems
	{
		0, 1, 2,
		2, 3, 0
	};

	std::vector<VertAttr> attrs
	{
		VertAttr{3},
		VertAttr{2},
	};

	return { verts, elems, attrs };
}