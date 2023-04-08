#include "mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Mesh::Mesh(
	unsigned int vertsCount, GLfloat* verts,
	unsigned int elemsCount, unsigned int* elems,
	unsigned int attrsCount, VertAttribute* attrs
)
	: VerticesCount{ vertsCount }, Vertices{ verts },
	  ElementsCount{ elemsCount }, Elements{ elems },
	  VertAttributesCount{ attrsCount }, VertAttributes{ attrs },
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
	glBufferData(GL_ARRAY_BUFFER, VerticesCount * sizeof(VerticesCount), Vertices, GL_STATIC_DRAW);

	// Set up the element buffer
	glGenBuffers(1, &ElementBufferObj);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementsCount * sizeof(ElementsCount), Elements, GL_STATIC_DRAW);

	// Configure the vertex attribute pointers
	auto stride{ 0u };
	auto attrSize = sizeof(float);
	for (auto loc{ 0u }; loc < VertAttributesCount; loc++)
	{
		stride += VertAttributes[loc].Count * attrSize;
	}

	// Tell OpenGL how our attribute is laid out in the array
	auto offset{ 0u };
	for (auto loc{ 0u }; loc < VertAttributesCount; loc++)
	{
		auto attr = VertAttributes[loc];
		glVertexAttribPointer(loc, attr.Count, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(loc); // Must also enable it!
		offset += attr.Count * attrSize;
	}
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
	glDrawElements(GL_TRIANGLES, ElementsCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
