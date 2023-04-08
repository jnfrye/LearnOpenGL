#include "shader.h"
#include "io.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

bool TryCompileShader(const std::string& shaderFileName, GLenum shaderType, unsigned int& outShader)
{
	std::string shaderSource;
	if (!TryReadFile("shaders\\" + shaderFileName, shaderSource))
	{
		return false;
	}

	const char* sourceText = shaderSource.c_str();

	outShader = glCreateShader(shaderType); // Create the shader, get the ID
	glShaderSource(outShader, 1, &sourceText, NULL); // Attach the shader source
	glCompileShader(outShader); // Compile!

	int success;
	glGetShaderiv(outShader, GL_COMPILE_STATUS, &success); // Check if it compiled...

	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(outShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR COMPILING VERTEX SHADER:\n" << infoLog << std::endl;
		return false;
	}

	return true;
}

bool TryLinkShaders(unsigned int vertexShader, unsigned int fragmentShader, unsigned int& shaderProgram)
{
	shaderProgram = glCreateProgram();
	std::cout << "PROGRAM ID 1: " << shaderProgram << std::endl;
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); // Check if it linked...

	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR LINKING SHADERS:\n" << infoLog << std::endl;
		return false;
	}

	return true;
}

bool TryCompileAndLinkShaders(const std::string& vertShaderFileName, const std::string& fragShaderFileName, unsigned int& shaderProgram)
{
	unsigned int vertexShader;
	if (!TryCompileShader(vertShaderFileName, GL_VERTEX_SHADER, vertexShader))
	{
		return false;
	}

	std::cout << "VERT SHADER ID: " << vertexShader << std::endl;

	unsigned int fragmentShader;
	if (!TryCompileShader(fragShaderFileName, GL_FRAGMENT_SHADER, fragmentShader))
	{
		return false;
	}

	std::cout << "FRAG SHADER ID: " << fragmentShader << std::endl;

	if (!TryLinkShaders(vertexShader, fragmentShader, shaderProgram))
	{
		return false;
	}

	std::cout << "PROGRAM ID 2: " << shaderProgram << std::endl;

	// The shader objects are no longer needed after linking
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}