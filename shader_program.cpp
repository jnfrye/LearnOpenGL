#include "shader_program.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>


ShaderProgram::ShaderProgram(const std::string& assetName)
	: AssetName{ assetName },
	  Program{ }
{ }

void ShaderProgram::CleanUp()
{
	glDeleteProgram(Program);
}

bool ShaderProgram::TryCompileAndLinkShaders()
{
	Shader vertShader{ Shader::EType::Vert };
	if (!vertShader.TryCompile(AssetName))
		return false;

	Shader fragShader{ Shader::EType::Frag };
	if (!fragShader.TryCompile(AssetName))
		return false;

	if (!TryLinkShaders(vertShader.ObjectID, fragShader.ObjectID))
		return false;

	// The shader objects are no longer needed after linking
	vertShader.CleanUp();
	fragShader.CleanUp();

	return true;
}

bool ShaderProgram::TryLinkShaders(unsigned int vertShader, unsigned int fragShader)
{
	Program = glCreateProgram();
	glAttachShader(Program, vertShader);
	glAttachShader(Program, fragShader);
	glLinkProgram(Program);

	int success;
	glGetProgramiv(Program, GL_LINK_STATUS, &success); // Check if it linked...

	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(Program, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR LINKING SHADERS:\n" << infoLog << std::endl;
		return false;
	}

	return true;
}