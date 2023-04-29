#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


class Shader
{
public:
	enum class EType
	{
		Invalid = 0,
		Vert,
		Frag
	};

	unsigned int ObjectID;

private:
	const EType Type;

public:
	Shader(EType type);
	void CleanUp();
	bool TryCompile(const std::string& assetName);
};