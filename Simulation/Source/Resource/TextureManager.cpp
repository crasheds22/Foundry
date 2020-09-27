#include "Resource/TextureManager.h"

namespace Resource
{
	bool TextureManager::Create(const std::string path, std::string name)
	{
		if (name.length() > 0)
		{
			if (!Find(name))
			{
				Texture temp(name, path.c_str());

				return Manager::Create(name, temp);
			}
		}

		Texture temp(name, path.c_str());

		return Manager::Create(temp.Name(), temp);
	}
}
