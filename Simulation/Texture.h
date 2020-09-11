#pragma once

#include <glad/glad.h>

class Texture
{
public:
	static unsigned int New(const char* path);

	static void FlipVertically();

private:
	Texture() { };
	Texture(const Texture& T) { };
	~Texture() { };
};

