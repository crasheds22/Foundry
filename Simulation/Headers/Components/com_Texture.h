#pragma once

#include <string>

#include "Resource/ResourceManager.h"

namespace Component
{
	class com_Texture
	{
	public:
		com_Texture() { mTexture = nullptr; }
		com_Texture(std::string name);
		~com_Texture() { mTexture = nullptr; }

		unsigned int TextureID() const;
		std::string TextureName() const;

	private:
		Texture* mTexture;
	};
}
