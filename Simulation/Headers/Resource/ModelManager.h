#pragma once

#include "Manager.h"
#include "Singleton.h"

#include "Graphics/Model.h"

namespace Resource
{
	/** @class ModelManager
	 *
	 *	@brief manages all models that are loaded for use in the game
	 *
	 *	@author Aaron Thomson
	 */
	class ModelManager
		: public Manager<Model>, public Singleton<ModelManager>
	{
	public:
		/** @brief Destructor
		 */
		~ModelManager();

		/** @brief Creates a model to be stored and used later
		 */
		bool Create(const std::string path, std::string name = "");

	private:

	};

	/** @class WorldManager
	 *
	 *	@breif Manages all worlds that can be used for the game
	 *
	 *	@author Aaron Thomson
	 */
	class WorldManager
		: public Manager<World>, public Singleton<WorldManager>
	{
	public:
		/** @brief Destructor
		 */
		~WorldManager();

		/** @brief Creates a new world model to be used in the game
		 */
		bool Create(const std::string path, std::string name = "");

	private:

	};
}
