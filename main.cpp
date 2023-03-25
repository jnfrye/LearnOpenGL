#include "window.h"
#include "shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	InitializeGLFW();

	GLFWwindow* window = CreateWindow();
	if (!window)
	{
		return -1;
	}

	unsigned int shaderProgram;
	if (!TryCompileAndLinkShaders(shaderProgram))
	{
		return -1;
	}

	// Gotta buffer the vertex data!!!
	// Notice each coordinate is in normalized device coordinates (-1 to 1)
	// With a z-coord of 0, the depth is the same for each
	GLfloat myTriangle[] = {
		-0.5f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
	};

	unsigned int elementIndices[] = {
		1, 2, 3,
		0, 2, 1
	};

	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	BufferVertexData(sizeof(myTriangle), myTriangle, sizeof(elementIndices), elementIndices, vao, vbo, ebo);

	while (window && !glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		// ---------- rendering START!

		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(elementIndices), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// ---------- rendering END!

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteProgram(shaderProgram);
	glfwTerminate();

	return 0;
}
