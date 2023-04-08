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

	unsigned int mesh1shader;
	if (!TryCompileAndLinkShaders("simple1.vert", "simple1.frag", mesh1shader))
		return -1;

	unsigned int mesh2shader;
	if (!TryCompileAndLinkShaders("simple2.vert", "simple2.frag", mesh2shader))
		return -1;

	GLfloat mesh1Verts[] =
	{	// X   // Y   // Z 	// R  // G  // B
		-0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f,
		 0.0f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f,
	};

	unsigned int mesh1Elems[] =
	{
		1, 2, 3,
		0, 2, 1
	};

	VertAttr mesh1Attrs[] =
	{
		VertAttr{3},
		VertAttr{3},
	};

	Mesh mesh1
	{
		std::size(mesh1Verts), mesh1Verts,
		std::size(mesh1Elems), mesh1Elems,
		std::size(mesh1Attrs), mesh1Attrs,
	};

	mesh1.Initialize();

	GLfloat mesh2Verts[] =
	{	// X   // Y   // Z  
		-1.0f,  1.0f,  0.0f,
		-0.8f,  0.0f,  0.0f,
		-1.0f, -1.0f,  0.0f,
	};

	unsigned int mesh2Elems[] =
	{
		0, 1, 2
	};

	VertAttr mesh2Attrs[] =
	{
		VertAttr{3},
	};

	Mesh mesh2
	{
		std::size(mesh2Verts), mesh2Verts,
		std::size(mesh2Elems), mesh2Elems,
		std::size(mesh2Attrs), mesh2Attrs,
	};

	mesh2.Initialize();

	while (window && !glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		// ---------- rendering START

		glClearColor(0.2f, 0.175f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float runTime = glfwGetTime();
		float oscillation = sin(runTime) / 2.0f + 0.5f;
		int myColorLocation = glGetUniformLocation(mesh1shader, "MyColor");
		glUseProgram(mesh1shader);
		glUniform4f(myColorLocation, 1.0f - oscillation, oscillation, 0.0f, 1.0f);
		mesh1.Draw();

		glUseProgram(mesh2shader);
		mesh2.Draw();

		// ---------- rendering END

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	mesh1.CleanUp();
	glDeleteProgram(mesh1shader);

	mesh2.CleanUp();
	glDeleteProgram(mesh2shader);

	glfwTerminate();

	return 0;
}
