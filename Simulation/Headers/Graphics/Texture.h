#pragma once

#include <string>

/** @enum TextureType
 *
 *	@brief Defines the types of textures you may come across
 *
 *	@author Aaron Thomson
 */
enum class TextureType
{
	DIFFUSE,
	NORMAL,
	HEIGHT,
	AMBIENT,
	SPECULAR,

};

/** @class Texture
 *
 *	@brief Loads and holds information related to a texture
 *
 *	@author Aaron Thomson
 */
class Texture
{
public:
	/** @brief Constructor
	 */
	Texture(const char* path, TextureType type = TextureType::DIFFUSE, std::string name = "");

	/** @brief Returns the texture ID
	 */
	unsigned int ID() const;
	
	/** @brief Returns the name of the texture  
	 */
	std::string Name() const;
	
	/** @brief Returns the file path to the texture
	 */
	std::string FilePath() const;
	
	/** @brief Returns the type of texture
	 */
	TextureType Type() const;

private:
	unsigned int mID;		/*!< The texture ID */
	std::string mName;		/*!< The name of the texture */
	std::string mFilePath;	/*!< The path to the texture */
	TextureType mType;		/*!< The type of texture */
};

/** @class TextureLoader
 *
 *	@brief Static class to load a texture
 *
 *	@author Aaron Thomson
 */
class TextureLoader
{
public:
	/** @brief Loads and creates a new texture
	 */
	static unsigned int New(const char* path);

	/** @brief Flips loaded textures vertically
	 */
	static void FlipVertically();

private:

};

