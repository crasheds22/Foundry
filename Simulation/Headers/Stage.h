#pragma once

#include "Resource/ResourceManager.h"

#include "Manager.h"

#include "ECS/Types.h"

#include "Components/Components.h"

#include "Systems/Systems.h"

#include "Prototype/PrototypeFactory.h"

/** @class Stage
 *
 *	@brief A game scene holding al the information needed for a game level to play
 *
 *	@author Aaron Thomson
 */
class Stage
	: public Manager<Prototype::IPrototype*>
{
public:
	/** @brief Constructor
	 */
	Stage();
	/** @brief Destructor
	 */
	~Stage();

	/** @brief Initialises the scene
	 */
	void Init();

	/** @brief Called once a frame to update the world
	 */
	void Update();

private:
	Resource::ResourceManager* mResources = nullptr;	/*!< Pointer to the resource manager */

	Component::com_Camera mCamera;	/*!< The camera for the scene */

	std::shared_ptr<System::sys_PlayerControl> PlayerSys;	/*!< The player system being used */
	std::shared_ptr<System::sys_Render> RenderSys;			/*!< The render system being used */
	std::shared_ptr<System::sys_Physics> PhysicsSys;		/*!< The physics system being used */
};

