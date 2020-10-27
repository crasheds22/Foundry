#pragma once

#include "Resource/ResourceManager.h"

namespace Component
{
	class com_Render
	{
	public:
		com_Render() { mModel = nullptr; mShader = nullptr; }
		com_Render(std::string modelName, std::string shaderName);
		~com_Render() { mModel = nullptr; mShader = nullptr; }

		Model* _Model() const;
		Shader* _Shader() const;

	private:
		Model* mModel = nullptr;
		Shader* mShader = nullptr;
	};
}
