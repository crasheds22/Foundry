#include "com_Texture.h"

#include "../Graphics/Texture.h"

namespace Component
{
	com_Texture::com_Texture(std::string path)
		: com_Texture(path.c_str())
	{

	}

	com_Texture::com_Texture(const char* path)
	{
		mID = Texture::New(path);
	}

	unsigned int com_Texture::ID() const
	{
		return mID;
	}
}
