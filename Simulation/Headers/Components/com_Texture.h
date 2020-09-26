#pragma once

#include <string>

#include "Graphics/Texture.h"
#include "Resource/ResourceManager.h"

namespace Component
{
	class com_Texture
	{
	public:
		com_Texture() { mTexture = nullptr; }
		com_Texture(std::string name);
		com_Texture(std::string name, std::string filepath);
		~com_Texture() { mTexture = nullptr; }

		unsigned int ID() const;
		std::string Name() const;

	private:
		Texture* mTexture;
	};
}
