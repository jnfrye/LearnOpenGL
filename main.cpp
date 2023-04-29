#include "window.h"
#include "shader_program.h"
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

	ShaderProgram mesh1shader("simple1");
	if (!mesh1shader.TryCompileAndLinkShaders())
		return -2;

	ShaderProgram mesh2shader("simple2");
	if (!mesh2shader.TryCompileAndLinkShaders())
		return -3;

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

		{
			glUseProgram(mesh1shader.Program);
			float runTime = glfwGetTime();
			float oscillation = sin(runTime) / 2.0f + 0.5f;
			int myColorLocation = glGetUniformLocation(mesh1shader.Program, "MyColor");
			glUniform4f(myColorLocation, 1.0f - oscillation, oscillation, 0.0f, 1.0f);
			parallelogram.Draw();
		}

		{
			glUseProgram(mesh2shader.Program);
			constexpr float period = 2.0f;
			float runTime = glfwGetTime();
			float phase = (runTime - period * floor(runTime / period)) / period; // normalized
			int phaseLocation = glGetUniformLocation(mesh2shader.Program, "Phase");
			glUniform1f(phaseLocation, phase);
			triangle.Draw();
		}

		// ---------- rendering END

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	parallelogram.CleanUp();
	mesh1shader.CleanUp();

	triangle.CleanUp();
	mesh2shader.CleanUp();

	glfwTerminate();

	return 0;
}
