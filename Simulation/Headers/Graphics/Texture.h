#pragma once

#include <string>

enum class TextureType
{
	DIFFUSE,
	NORMAL,
	HEIGHT,
	AMBIENT,
	SPECULAR,

};

class Texture
{
public:
	Texture(const char* path, TextureType type = TextureType::DIFFUSE, std::string name = "");

	unsigned int ID() const;
	std::string Name() const;
	std::string FilePath() const;
	TextureType Type() const;

private:
	unsigned int mID;
	std::string mName;
	std::string mFilePath;
	TextureType mType;
};

class TextureLoader
{
public:
	static unsigned int New(const char* path);

	static void FlipVertically();

private:

};

