#pragma once

#include <string>

namespace Component
{
	class Texture
	{
	public:
		Texture(std::string path);
		Texture(const char* path);
		~Texture();

		unsigned int ID() const;

	private:
		unsigned int mID;
	};
}
