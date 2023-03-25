#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void InitializeGLFW();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* CreateWindow();
