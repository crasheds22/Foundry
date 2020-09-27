#include "Resource/TextureManager.h"

namespace Resource
{
	bool TextureManager::Create(const std::string path, TextureType type, std::string name)
	{
		if (name.length() > 0)
		{
			if (!Find(name))
			{
				Texture temp(path.c_str(), type, name);

				return Manager::Create(name, temp);
			}

			return false;
		}

		Texture temp(path.c_str(), type);

		return Manager::Create(temp.Name(), temp);
	}
}
