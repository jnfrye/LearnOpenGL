#include "shader.h"
#include "io.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string>
#include <iostream>


static std::string GetExtension(Shader::EType type)
{
	switch (type)
	{
	case Shader::EType::Vert: return "vert";
	case Shader::EType::Frag: return "frag";
	default: throw std::invalid_argument("Invalid shader type: " + std::to_string(static_cast<int>(type)));
	}
}

static GLenum GetGLType(Shader::EType type)
{
	switch (type)
	{
	case Shader::EType::Vert: return GL_VERTEX_SHADER;
	case Shader::EType::Frag: return GL_FRAGMENT_SHADER;
	default: throw std::invalid_argument("Invalid shader type: " + std::to_string(static_cast<int>(type)));
	}
}

Shader::Shader(EType type)
	: Type{ type }, ObjectID{ }
{ }

void Shader::CleanUp()
{
	glDeleteShader(ObjectID);
}

bool Shader::TryCompile(const std::string& assetName)
{
	std::string shaderSource;
	if (!TryReadFile("shaders\\" + assetName + "." +  GetExtension(Type), shaderSource))
		return false;

	const char* sourceText = shaderSource.c_str();

	ObjectID = glCreateShader(GetGLType(Type)); // Create the shader, get the ID
	glShaderSource(ObjectID, 1, &sourceText, NULL); // Attach the shader source
	glCompileShader(ObjectID); // Compile!

	int success;
	glGetShaderiv(ObjectID, GL_COMPILE_STATUS, &success); // Check if it compiled...

	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(ObjectID, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR COMPILING SHADER:\n" << infoLog << std::endl;
		return false;
	}

	return true;
}