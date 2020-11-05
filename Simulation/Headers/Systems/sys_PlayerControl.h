#pragma once

#include "ECS/System.h"

#include "Props.h"

#include "Components/com_Camera.h"

namespace System
{
	/** @class sys_PlayerControl
	 *
	 *	@brief The system that handles and processes the player
	 *
	 *	@author Aaron Thomson
	 */
	class sys_PlayerControl
		: public ECS::System
	{
	public:
		/** @brief Initialises the system
		 */
		void Init();

		/** @brief Updates all the player entities
		 */
		void Update(Component::com_Camera* camera);

	private:
		Props* ref = nullptr;	/*!< A pointer to the props class */
	};
}
