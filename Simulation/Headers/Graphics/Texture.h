#pragma once

#include <glad/glad.h>

enum class TextureType
{
	DIFFUSE,
	NORMAL,
	HEIGHT,
	AMBIENT,
	SPECULAR,

};

class TextureLoader
{
public:
	static unsigned int New(const char* path);

	static void FlipVertically();

private:

};

