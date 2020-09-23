#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include "Manager.h"

#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

namespace Resource
{
	class ResourceManager
	{
	public:
		static ResourceManager& Instance();

		ResourceManager(const ResourceManager& rm) = delete;
		void operator=(const ResourceManager& rm) = delete;

		void CreateModel(std::string name, std::string filepath);
		void CreateTexture(std::string name, std::string filepath, TextureType type = TextureType::DIFFUSE);
		void CreateShader(std::string name, std::string vertex, std::string frag, std::string geo);

		Model* RetrieveModel(std::string name);
		Texture* RetrieveTexture(std::string name);
		unsigned int* RetrieveShader(std::string name);

	private:
		ResourceManager();

		Manager<Model> mModelManager;
		Manager<Texture> mTextureManager;
		Manager<unsigned int> mShaderManager;
	};
}

#endif
