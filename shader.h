#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool TryCompileShader(GLenum shaderType, unsigned int& outShader, const char* shaderSource);
bool TryLinkShaders(unsigned int vertexShader, unsigned int fragmentShader, unsigned int& shaderProgram);
bool TryCompileAndLinkShaders(unsigned int& shaderProgram);
