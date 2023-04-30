#pragma once

#include "shader.h"
#include "vector.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <string_view>


class ShaderProgram
{
public:
	unsigned int Program;

private:
	const std::string AssetName;

public:
	ShaderProgram(const std::string& assetName);
	void CleanUp();
	bool TryCompileAndLinkShaders();

	void Use();
	void SetUniform(const char* name, Vec4<float> value);
	void SetUniform(const char* name, float value);

private:
	bool TryLinkShaders(unsigned int vertShader, unsigned int fragShader);
};