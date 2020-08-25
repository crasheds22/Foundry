#include "Texture.h"

#include "../Graphics/Texture.h"
using StaticTexture = Texture;

namespace Component
{
	Texture::Texture(std::string path, bool flipV)
		: Texture(path.c_str(), flipV)
	{

	}

	Texture::Texture(const char* path, bool flipV)
	{
		mID = StaticTexture::New(path, flipV);
	}

	Texture::~Texture()
	{

	}

	unsigned int Texture::ID() const
	{
		return mID;
	}
}
