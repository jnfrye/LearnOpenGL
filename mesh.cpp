#include "mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Mesh::Mesh(
	std::vector<GLfloat>& verts,
	std::vector<unsigned int>& elems,
	std::vector<VertAttr>& attrs
)
	: Verts{ verts }, Elems{ elems }, Attrs{ attrs },
	  VertBufferObj{ }, ElemBufferObj{ }, VertArrayObj{ }
{ }

void Mesh::Initialize()
{
	// Bind the VAO to store everything in
	glGenVertexArrays(1, &VertArrayObj);

	glBindVertexArray(VertArrayObj);

	// Set up the vertex buffer
	glGenBuffers(1, &VertBufferObj);
	glBindBuffer(GL_ARRAY_BUFFER, VertBufferObj); // Bind the buffer as the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, Verts.size() * sizeof(Verts.front()), Verts.data(), GL_STATIC_DRAW);

	// Set up the element buffer
	glGenBuffers(1, &ElemBufferObj);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElemBufferObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Elems.size() * sizeof(Elems.front()), Elems.data(), GL_STATIC_DRAW);

	// Configure the vertex attribute pointers
	auto stride{ 0u };
	auto attrSize = sizeof(float);
	for (auto attr : Attrs)
	{
		stride += attr.Count * attrSize;
	}

	// Tell OpenGL how our attribute is laid out in the array
	auto offset{ 0u };
	for (auto loc{ 0u }; loc < Attrs.size(); loc++)
	{
		auto attr = Attrs[loc];
		glVertexAttribPointer(loc, attr.Count, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(loc); // Must also enable it!
		offset += attr.Count * attrSize;
	}
}

void Mesh::CleanUp()
{
	glDeleteVertexArrays(1, &VertArrayObj);
	glDeleteBuffers(1, &VertBufferObj);
	glDeleteBuffers(1, &ElemBufferObj);
}

void Mesh::Draw()
{
	glBindVertexArray(VertArrayObj);
	glDrawElements(GL_TRIANGLES, Elems.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
