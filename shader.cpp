#include "shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

bool TryCompileShader(GLenum shaderType, unsigned int& outShader, const char* shaderSource)
{
	outShader = glCreateShader(shaderType); // Create the shader, get the ID
	glShaderSource(outShader, 1, &shaderSource, NULL); // Attach the shader source
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

bool TryCompileAndLinkShaders(unsigned int& shaderProgram)
{
	unsigned int vertexShader;
	if (!TryCompileShader(GL_VERTEX_SHADER, vertexShader, "#version 330 core\nlayout (location = 0) in vec3 aPos; void main() { gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); }"))
	{
		return false;
	}

	std::cout << "VERT SHADER ID: " << vertexShader << std::endl;

	unsigned int fragmentShader;
	if (!TryCompileShader(GL_FRAGMENT_SHADER, fragmentShader, "#version 330 core\nout vec4 FragColor;\nvoid main() { FragColor = vec4(1.0f, 0.f, 0.f, 1.0f); }"))
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