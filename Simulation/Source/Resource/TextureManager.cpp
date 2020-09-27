#include "Resource/TextureManager.h"

namespace Resource
{
	bool TextureManager::Create(const std::string path, std::string name)
	{
		if (name.length() > 0)
		{
			if (!Find(name))
			{
				Texture temp(path.c_str(), name);

				return Manager::Create(name, temp);
			}

			return false;
		}

		Texture temp(path.c_str());

		return Manager::Create(temp.Name(), temp);
	}
}
