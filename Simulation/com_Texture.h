#pragma once

#include <string>

namespace Component
{
	class Texture
	{
	public:
		Texture() {};
		Texture(std::string path);
		Texture(const char* path);

		unsigned int ID() const;

	private:
		unsigned int mID{};
	};
}
