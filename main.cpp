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
	if (!TryCompileAndLinkShaders("simple.vert", "simple.frag", shaderProgram))
		return -1;

	GLfloat parallelogramVerts[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
	};

	unsigned int parallelogramElems[] =
	{
		1, 2, 3,
		0, 2, 1
	};

	Mesh parallelogramMesh{ sizeof(parallelogramVerts), parallelogramVerts, sizeof(parallelogramElems), parallelogramElems };
	parallelogramMesh.Initialize();

	GLfloat triangleVerts[] =
	{
		-1.0f,  1.0f, 0.0f,
		-0.8f,  0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
	};

	unsigned int triangleElems[] =
	{
		0, 1, 2
	};

	Mesh triangleMesh{ sizeof(triangleVerts), triangleVerts, sizeof(triangleElems), triangleElems };
	triangleMesh.Initialize();

	while (window && !glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		// ---------- rendering START

		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		parallelogramMesh.Draw();
		triangleMesh.Draw();

		// ---------- rendering END

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	parallelogramMesh.CleanUp();
	triangleMesh.CleanUp();
	glDeleteProgram(shaderProgram);
	glfwTerminate();

	return 0;
}
