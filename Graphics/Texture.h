#pragma once

class Texture
{
public:
	static unsigned int New(const char* path, bool flip = false, int channels = 3);

private:
	Texture() { };
	Texture(const Texture& T) { };
	~Texture() { };
};

