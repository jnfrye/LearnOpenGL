#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

bool TryCompileShader(const std::string& shaderFileName, GLenum shaderType, unsigned int& outShader);
bool TryLinkShaders(unsigned int vertexShader, unsigned int fragmentShader, unsigned int& shaderProgram);
bool TryCompileAndLinkShaders(const std::string& vertShaderFileName, const std::string& fragShaderFileName, unsigned int& shaderProgram);
