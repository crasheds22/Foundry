#include "Resource/ModelManager.h"

namespace Resource
{
	ModelManager::~ModelManager()
	{
		DeleteAll();
	}

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

	WorldManager::~WorldManager()
	{
		DeleteAll();
	}

	bool WorldManager::Create(const std::string path, std::string name)
	{
		if (name.length() > 0)
		{
			if (!Find(name))
			{
				World temp(path);

				return Manager::Create(name, temp);
			}

			return false;
		}

		World temp(path);

		return Manager::Create(temp.Name(), temp);
	}
}
