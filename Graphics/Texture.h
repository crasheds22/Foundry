#pragma once

class Texture
{
public:
	static unsigned int New(const char* path, bool flip = false);

private:
	Texture() { };
	Texture(const Texture& T) { };
	~Texture() { };
};

