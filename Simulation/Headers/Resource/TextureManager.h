#pragma once

#include "Manager.h"
#include "Singleton.h"

#include "Graphics/Texture.h"

namespace Resource
{
	class TextureManager
		: public Manager<Texture>, public Singleton<TextureManager>
	{
	public:
		bool Create(const std::string path, std::string name = "");

	private:

	};
}
