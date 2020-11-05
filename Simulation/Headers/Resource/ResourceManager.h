#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include "Manager.h"
#include "Singleton.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

namespace Resource
{
	/** @class ResourceManager
	 *
	 *	@brief Provides a central point of contact to all other resource managers
	 *
	 *	@author Aaron Thomson
	 */
	class ResourceManager
		: public Singleton<ResourceManager>
	{
	public:
		/** @brief Destructor
		 */
		~ResourceManager();

		/** @brief initialise all the pointers
		 */
		void Init();

		/** @brief Creates a model in the model manager
		 */
		void CreateModel	(std::string filepath, std::string name = "");
		
		/** @brief Creates a texture in the texture manager
		 */
		void CreateTexture	(std::string name, std::string filepath, TextureType type = TextureType::DIFFUSE);
		
		/** @brief Creates a shader in the shader manager 
		 */
		void CreateShader	(std::string name, const char* vertex, const char* frag, const char* geo = nullptr);
		
		/** @brief Creates a world model in the world manager
		 */
		void CreateWorld	(std::string filepath, std::string name = "");

		/** @brief Returns a model from the model manager specified by the name passed in 
		 */
		Model*		RetrieveModel(std::string name);
		
		/** @brief Returns a texture from the texture manager specified by the name passed in
		 */
		Texture*	RetrieveTexture(std::string name);
		
		/** @brief Returns a shader from the shader manager specified by the name passed in
		 */
		Shader*		RetrieveShader(std::string name);
		
		/** @brief Returns a world from the world manager specified by the name passed in
		 */
		World*		RetrieveWorld(std::string name);

		/** @brief Constructor
		 */
		ResourceManager();

	private:
		ModelManager*   mModelManager	= nullptr;	/*!< Pointer to the model manager */
		TextureManager* mTextureManager = nullptr;	/*!< Pointer to the texture manager */
		ShaderManager*  mShaderManager	= nullptr;	/*!< Pointer to the shader manager */
		WorldManager*	mWorldManager	= nullptr;	/*!< POinter to the world manager */
	};
}

#endif
