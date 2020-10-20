#pragma once

#include "Resource/ResourceManager.h"

#include "Manager.h"

#include "ECS/Types.h"

#include "Components/Components.h"

#include "Systems/Systems.h"

/**
*	\class Stage
*
*	\brief Class to manage game loop
*/
class Stage
	: public Manager<ECS::Entity>
{
public:
	/**
	*	\brief Default constructor
	* 
	*	\post Stage is constructed
	*/
	Stage();
	/**
	*	\brief Destructor
	* 
	*	\post Stage is destructed
	*/
	~Stage();

	/**
	*	\brief Initialise
	* 
	*	Initialises system and creates entities
	* 
	*	\post Systems are initialised and entities are created
	*/
	void Init();

	/**
	*	\brief Update
	* 
	*	\post The render system and player system are updated
	*/
	void Update();

private:
	Resource::ResourceManager* mResources = nullptr;	/*!< Resource manager variable*/

	Component::com_Camera mCamera;	/*!< Camera variable*/

	std::shared_ptr<System::sys_PlayerControl> PlayerSys;	/*!< Player system variable*/
	std::shared_ptr<System::sys_Render> RenderSys;			/*!< Render system variable*/
};

