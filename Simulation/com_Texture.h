#pragma once

#include <string>

namespace Component
{
	class Texture
	{
	public:
		Texture() {};
		Texture(const Texture& t) {};
		Texture(std::string path);
		Texture(const char* path);
		~Texture();

		unsigned int ID() const;

	private:
		unsigned int mID{};
	};
}
