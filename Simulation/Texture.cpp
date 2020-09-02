#include "Texture.h"

#include "../Graphics/Texture.h"
using StaticTexture = Texture;

namespace Component
{
	Texture::Texture(std::string path)
		: Texture(path.c_str())
	{

	}

	Texture::Texture(const char* path)
	{
		mID = StaticTexture::New(path);
	}

	Texture::~Texture()
	{

	}

	unsigned int Texture::ID() const
	{
		return mID;
	}
}
