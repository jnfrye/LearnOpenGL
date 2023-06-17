#pragma once

#include <string>

class Texture
{
public:
	unsigned int ObjectID{ };

	Texture();

	bool TryLoad(const char* assetPath);
};

