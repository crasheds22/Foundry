#pragma once

#include "Manager.h"
#include "Singleton.h"

#include "Graphics/Shader.h"

namespace Resource
{
	/** @class ShaderManager
	 *
	 *	@brief Manages shaders that are loaded for use in the game
	 *
	 *	@author Aaron Thomson
	 */
	class ShaderManager
		: public Manager<Shader>, public Singleton<ShaderManager>
	{
	public:
		/** @brief Destructor
		 */
		~ShaderManager();

		/** @brief Creates a new shader for use in the game
		 */
		bool Create(std::string name, const char* frag, const char* vert, const char* geo = nullptr);

	private:
	};
}
