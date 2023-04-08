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
	{	// X   // Y   // Z 	// R  // G  // B
		-0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f,
		 0.0f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f,
	};

	unsigned int parallelogramElems[] =
	{
		1, 2, 3,
		0, 2, 1
	};

	VertAttribute parallelogramAttrs[] =
	{
		VertAttribute{3},
		VertAttribute{3},
	};

	Mesh parallelogramMesh
	{
		std::size(parallelogramVerts), parallelogramVerts,
		std::size(parallelogramElems), parallelogramElems,
		std::size(parallelogramAttrs), parallelogramAttrs,
	};

	parallelogramMesh.Initialize();

	GLfloat triangleVerts[] =
	{	// X   // Y   // Z  
		-1.0f,  1.0f,  0.0f,
		-0.8f,  0.0f,  0.0f,
		-1.0f, -1.0f,  0.0f,
	};

	unsigned int triangleElems[] =
	{
		0, 1, 2
	};

	VertAttribute triangleAttrs[] =
	{
		VertAttribute{3},
	};

	Mesh triangleMesh
	{
		std::size(triangleVerts), triangleVerts,
		std::size(triangleElems), triangleElems,
		std::size(triangleAttrs), triangleAttrs,
	};

	triangleMesh.Initialize();

	while (window && !glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		// ---------- rendering START

		glClearColor(0.2f, 0.175f, 0.25f, 1.0f);
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
	glDeleteProgram(shaderProgram1);

	triangleMesh.CleanUp();
	glDeleteProgram(shaderProgram2);

	glfwTerminate();

	return 0;
}
