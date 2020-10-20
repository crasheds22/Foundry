#pragma once

#include <string>

#include "Resource/ResourceManager.h"

/**
*	\namespace Component
*
*	The namespace all Components are located in.
*/
namespace Component
{
	/**
	*	\class com_Texture
	* 
	*	\brief Class to hold all the information about textures
	*/
	class com_Texture
	{
	public:
		/**
		*	\brief Default constructor
		* 
		*	Not to be used
		*/
		com_Texture() { mTexture = nullptr; }
		/**
		*	\brief Constructor
		* 
		*	\param [in] name	filename of texture
		*	\post Texture is constructed with the values passed in
		*/
		com_Texture(std::string name);
		/**
		*	\brief Destructor
		* 
		*	\post Texture is destructed
		*/
		~com_Texture() { mTexture = nullptr; }

		/**
		*	\brief Texture ID accessor
		* 
		*	\return mTexture->ID
		*	\post mTexture->ID is returned, but unchanged
		*/
		unsigned int TextureID() const;
		/**
		*	\brief Texture name accessor
		* 
		*	\return mTexture->Name
		*	\post mTexture->Name is returned, but unchanged
		*/
		std::string TextureName() const;

	private:
		Texture* mTexture;	/*!< Texture variable*/
	};
}
