#pragma once

#include "Manager.h"
#include "Singleton.h"

#include "Graphics/Shader.h"

namespace Resource
{
	class ShaderManager
		: public Manager<Shader>, public Singleton<ShaderManager>
	{
	public:
		~ShaderManager();

		bool Create(std::string name, const char* frag, const char* vert, const char* geo = nullptr);

	private:
	};
}
