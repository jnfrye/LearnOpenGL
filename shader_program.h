#pragma once

#include "shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


class ShaderProgram
{
public:
	unsigned int Program;

private:
	const std::string AssetName;

public:
	ShaderProgram(const std::string& assetName);
	bool TryCompileAndLinkShaders();
	void CleanUp();

private:
	bool TryLinkShaders(unsigned int vertShader, unsigned int fragShader);
};