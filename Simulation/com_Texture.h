#pragma once

#include <string>

#include "Texture.h"

namespace Component
{
	class com_Texture
	{
	public:
		com_Texture() {};
		com_Texture(std::string path);
		com_Texture(const char* path);

		unsigned int ID() const;

	private:
		unsigned int mID{};
	};
}
