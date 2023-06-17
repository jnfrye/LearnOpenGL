#include "window.h"
#include "shader_program.h"
#include "mesh.h"
#include "texture.h"
#include "mesh_factory.h"
#include "vector.h"

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

	ShaderProgram squareShader("texture1");
	if (!squareShader.TryCompileAndLinkShaders())
		return -4;

	// These only need to be set once
	squareShader.Use();
	squareShader.SetUniform("TexData0", 0);
	squareShader.SetUniform("TexData1", 1);

	Texture texture0;
	if (!texture0.TryLoad("textures/awesomeface.png"))
		return -5;

	Texture texture1;
	if (!texture1.TryLoad("textures/container.jpg"))
		return -6;

	Mesh parallelogram = MeshFactory::CreateParallelogram();
	parallelogram.Initialize();

	Mesh triangle = MeshFactory::CreateTriangle();
	triangle.Initialize();

	Mesh square = MeshFactory::CreateSquare();
	square.Initialize();

	while (window && !glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		// ---------- rendering START

		glClearColor(0.2f, 0.175f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		{
			mesh1shader.Use();

			double runTime = glfwGetTime();
			float oscillation = sin(runTime) / 2.0f + 0.5f;

			mesh1shader.SetUniform("MyColor", Vec4<float>{ 1.0f - oscillation, oscillation, 0.0f, 1.0f });
			parallelogram.Draw();
		}

		{
			mesh2shader.Use();

			constexpr float period = 2.0f;
			double runTime = glfwGetTime();
			float phase = (runTime - period * floor(runTime / period)) / period; // normalized
			
			mesh2shader.SetUniform("Phase", phase);
			triangle.Draw();
		}

		{
			squareShader.Use();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture0.ObjectID);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture1.ObjectID);

			square.Draw();
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
