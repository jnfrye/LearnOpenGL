#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

constexpr int WINDOW_INITIAL_WIDTH = 800;
constexpr int WINDOW_INITIAL_HEIGHT = 600;

void InitializeGLFW()
{
	glfwInit();

	// Tell GLFW we're using OpenGL 3.3 spec
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW we want to be restricted to the "core" profile of functionality
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Callback that resizes the viewport we draw to whenever the OS window is resized
	glViewport(0, 0, width, height);
}

GLFWwindow* CreateWindow()
{
	GLFWwindow* window = glfwCreateWindow(WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT, "Hello, world!", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	// Loads all the OpenGL function pointers from the graphics card drivers
	if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}

	// Create a viewport in the current OS window, start drawing at lower left corner, fill whole window.
	glViewport(0, 0, WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}
