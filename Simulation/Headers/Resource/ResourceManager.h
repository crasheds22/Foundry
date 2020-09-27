#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include "Manager.h"
#include "Singleton.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

namespace Resource
{
	class ResourceManager
		: public Singleton<ResourceManager>
	{
	public:
		void Init();

		void CreateModel(std::string filepath, std::string name = "");
		void CreateTexture(std::string name, std::string filepath, TextureType type = TextureType::DIFFUSE);
		void CreateShader(std::string name, const char* vertex, const char* frag, const char* geo = nullptr);

		Model* RetrieveModel(std::string name);
		Texture* RetrieveTexture(std::string name);
		Shader* RetrieveShader(std::string name);

	private:
		ModelManager*   mModelManager = nullptr;
		TextureManager* mTextureManager = nullptr;
		ShaderManager*  mShaderManager = nullptr;
	};
}

#endif
