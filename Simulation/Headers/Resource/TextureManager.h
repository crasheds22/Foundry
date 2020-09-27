#pragma once

#include "Manager.h"
#include "Singleton.h"

#include "Graphics/Texture.h"

namespace Resource
{
	class TextureManager
		: public Manager<Texture>, public Singleton
	{
	};
}
