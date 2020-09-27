#include "Components/com_Render.h"

namespace Component
{
	com_Render::com_Render(std::string modelName, std::string shaderName)
	{
		mModel =  Resource::ResourceManager::Instance().RetrieveModel(modelName);
		mShader = Resource::ResourceManager::Instance().RetrieveShader(shaderName);
	}

	Model* com_Render::_Model() const
	{
		return mModel;
	}

	Shader* com_Render::_Shader() const
	{
		return mShader;
	}
}
