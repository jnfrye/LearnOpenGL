#include "window.h"
#include "shader.h"
#include "mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

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

	std::vector<GLfloat> mesh1Verts =
	{	// X   // Y   // Z 	// R  // G  // B
		-0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f,
		 0.0f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f,
	};

	std::vector<unsigned int> mesh1Elems =
	{
		1, 2, 3,
		0, 2, 1
	};

	std::vector<VertAttr> mesh1Attrs =
	{
		VertAttr{3},
		VertAttr{3},
	};

	Mesh mesh1 { mesh1Verts, mesh1Elems, mesh1Attrs };

	mesh1.Initialize();

	std::vector<GLfloat> mesh2Verts =
	{	// X   // Y   // Z  
		-1.0f,  1.0f,  0.0f,
		-0.8f,  0.0f,  0.0f,
		-1.0f, -1.0f,  0.0f,
	};

	std::vector<unsigned int> mesh2Elems =
	{
		0, 1, 2
	};

	std::vector<VertAttr> mesh2Attrs =
	{
		VertAttr{3},
	};

	Mesh mesh2{ mesh2Verts, mesh2Elems, mesh2Attrs };

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
