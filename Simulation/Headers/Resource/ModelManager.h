#pragma once

#include "Manager.h"
#include "Singleton.h"

#include "Graphics/Model.h"

namespace Resource
{
	class ModelManager
		: public Manager<Model>, public Singleton<ModelManager>
	{
	public:
		~ModelManager();

		bool Create(const std::string path, std::string name = "");

	private:

	};

	class WorldManager
		: public Manager<World>, public Singleton<WorldManager>
	{
	public:
		~WorldManager();

		bool Create(const std::string path, std::string name = "");

	private:

	};
}
