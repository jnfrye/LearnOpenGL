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

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
	};

	unsigned int elements[] =
	{
		1, 2, 3,
		0, 2, 1
	};

	Mesh myMesh{ sizeof(vertices), vertices, sizeof(elements), elements };
	myMesh.Initialize();

	while (window && !glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		// ---------- rendering START

		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		myMesh.Draw();

		// ---------- rendering END

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	myMesh.CleanUp();
	glDeleteProgram(shaderProgram);
	glfwTerminate();

	return 0;
}
