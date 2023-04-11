#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "mesh_factory.h"

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

	Mesh parallelogram = MeshFactory::CreateParallelogram();
	parallelogram.Initialize();

	Mesh triangle = MeshFactory::CreateTriangle();
	triangle.Initialize();

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
		parallelogram.Draw();

		glUseProgram(mesh2shader);
		triangle.Draw();

		// ---------- rendering END

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	parallelogram.CleanUp();
	glDeleteProgram(mesh1shader);

	triangle.CleanUp();
	glDeleteProgram(mesh2shader);

	glfwTerminate();

	return 0;
}
