#include "window.h"
#include "shader.h"
#include "mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
		return -1;

	unsigned int shaderProgram;
	if (!TryCompileAndLinkShaders(shaderProgram))
		return -1;

	GLfloat myTriangle[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
	};

	unsigned int elementIndices[] =
	{
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
