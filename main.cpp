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

	unsigned int shaderProgram1;
	if (!TryCompileAndLinkShaders("simple1.vert", "simple1.frag", shaderProgram1))
		return -1;

	unsigned int shaderProgram2;
	if (!TryCompileAndLinkShaders("simple2.vert", "simple2.frag", shaderProgram2))
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

		glClearColor(0.1f, .5f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float runTime = glfwGetTime();
		float oscillation = sin(runTime) / 2.0f + 0.5f;
		int myColorLocation = glGetUniformLocation(shaderProgram1, "MyColor");
		glUseProgram(shaderProgram1);
		glUniform4f(myColorLocation, 1.0f - oscillation, oscillation, 0.0f, 1.0f);
		parallelogramMesh.Draw();

		glUseProgram(shaderProgram2);
		triangleMesh.Draw();

		// ---------- rendering END

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	parallelogramMesh.CleanUp();
	triangleMesh.CleanUp();
	glDeleteProgram(shaderProgram1);
	glDeleteProgram(shaderProgram2);
	glfwTerminate();

	return 0;
}
