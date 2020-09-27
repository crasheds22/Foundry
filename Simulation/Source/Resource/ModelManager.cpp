#include "Resource/ModelManager.h"

namespace Resource
{
	bool ModelManager::Create(const std::string path, std::string name)
	{
		if (name.length() > 0)
		{
			if (!Find(name))
			{
				Model temp(path);

				return Manager::Create(name, temp);
			}

			return false;
		}

		Model temp(path);
		
		return Manager::Create(temp.Name(), temp);
	}
}
