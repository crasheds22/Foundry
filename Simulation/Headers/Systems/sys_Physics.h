#pragma once

#include "ECS/System.h"

#include "Components/com_Physics.h"
#include "Components/com_Transform.h"
#include "Components/Collider.h"

#include "Algorithms/Physics.h"
#include "Props.h"

#include <vector>

namespace System
{
	/** @class sys_Physics
	 *
	 *	@brief A system to loop through and update all entities with a physics component
	 *
	 *	@author Nicholas Subianto
	 */
	class sys_Physics : public ECS::System
	{
	public:
		/** @brief Initialises the system
		 */
		void Init();

		/** @brief Updates all the player entities in three steps, collision detection, resolution and force application
		 */
		void Update();

	private:
		std::vector<Collision> CollisionList;  /*!< A vector of detected, unique collision pairs to resolve */
		Props* ref = nullptr;				   /*!< A pointer to the props class */
	};
}