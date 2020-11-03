#pragma once

#include <string>

#include "Resource/ResourceManager.h"

namespace Component
{
	/** @class com_Texture
	 *
	 *	@brief A component for displaying and holding a texture
	 *
	 *	@author Aaron Thomson
	 */
	class com_Texture
	{
	public:
		/** @brief Constructor
		 */
		com_Texture() { mTexture = nullptr; }
		
		/** @brief Constructor 
		 *
		 *	@param name The name of the texture to use
		 */
		com_Texture(std::string name);
		
		/** @brief Destructor
		 */
		~com_Texture() { mTexture = nullptr; }

		/** @brief Returns the ID of the texture 
		 */
		unsigned int TextureID() const;
		
		/** @brief Returns the name of the texture being used
		 */
		std::string TextureName() const;

	private:
		Texture* mTexture;	/*<! A pointer to the texture object */
	};
}
