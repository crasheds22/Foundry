#include "Resource/ShaderManager.h"

namespace Resource
{
	bool ShaderManager::Create(std::string name, const char* frag, const char* vert, const char* geo)
	{
		if (!Find(name))
		{
			Shader temp(name, frag, vert, geo);

			return Manager::Create(name, temp);
		}

		return false;
	}
}
