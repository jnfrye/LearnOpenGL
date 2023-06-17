#pragma once

#include "mesh.h"

class MeshFactory
{
public:
	static Mesh CreateTriangle();
	static Mesh CreateParallelogram();
	static Mesh CreateSquare();
};