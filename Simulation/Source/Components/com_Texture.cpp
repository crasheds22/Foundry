#include "Components/com_Texture.h"

namespace Component
{
	com_Texture::com_Texture(std::string name)
	{
		mTexture = Resource::ResourceManager::Instance().RetrieveTexture(name);
	}

	unsigned int com_Texture::TextureID() const
	{
		return mTexture->ID();
	}
	
	std::string com_Texture::TextureName() const
	{
		return mTexture->Name();
	}
}
