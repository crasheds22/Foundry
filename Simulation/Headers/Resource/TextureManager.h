#pragma once

#include "Manager.h"
#include "Singleton.h"

#include "Graphics/Texture.h"

namespace Resource
{
	/** @class TextureManager
	 *
	 *	@brief Manages textures that are loaded for use in the game
	 *
	 *	@author Aaron Thomson
	 */
	class TextureManager
		: public Manager<Texture>, public Singleton<TextureManager>
	{
	public:
		/** @brief Destructor
		 */
		~TextureManager();

		/** @brief Creates a texture 
		 */
		bool Create(const std::string path, TextureType type = TextureType::DIFFUSE, std::string name = "");

	private:

	};
}
