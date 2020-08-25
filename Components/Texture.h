#pragma once

#include <string>

namespace Component
{
	class Texture
	{
	public:
		Texture(std::string path, bool flipV = false);
		Texture(const char* path, bool flipV = false);
		~Texture();

		unsigned int ID() const;

	private:
		unsigned int mID;
	};
}
