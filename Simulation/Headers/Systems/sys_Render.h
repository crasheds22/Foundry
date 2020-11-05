#pragma once

#include "ECS/System.h"

#include "Components/com_Camera.h"

#include "Graphics/Graphics.h"

namespace System
{
	/** @class sys_Render
	 *
	 *	@brief A system to loop through and render all renderable components and entities
	 *
	 *	@author Aaron Thomson
	 */
	class sys_Render : public ECS::System
	{
	public:
		/** @brief Initialises the system
		 */
		void Init();

		/** @brief Updates all renderable entities
		 */
		void Update(const Component::com_Camera* camera);

	private:

	};
}
