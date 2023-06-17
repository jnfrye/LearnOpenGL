#include "texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include <iostream>

Texture::Texture()
	: ObjectID{ }
{ }

bool Texture::TryLoad(const char* assetPath)
{
	// Create and bind texture object
	glGenTextures(1, &ObjectID);
	glBindTexture(GL_TEXTURE_2D, ObjectID);

	// Flip textures so they are not mirrored vertically
	stbi_set_flip_vertically_on_load(true);

	// Load texture data
	int width;
	int height;
	int numChannels;
	unsigned char* data = stbi_load(assetPath, &width, &height, &numChannels, 0);

	if (!data)
	{
		std::cout << "Failed to load texture '" << assetPath << "'" << std::endl;
		return false;
	}

	int inColorFormat;
	switch (numChannels)
	{
	case 3:
		inColorFormat = GL_RGB;
		break;
	case 4:
		inColorFormat = GL_RGBA;
		break;
	default:
		std::cout << "Unsupported number of color channels (" << numChannels << ") in texture '" << assetPath << "'" << std::endl;
		return false;
	}

	// Set wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Generate the texture and the mipmap levels
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, inColorFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	return true;
}
