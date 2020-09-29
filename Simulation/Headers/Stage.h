#pragma once

#include "Resource/ResourceManager.h"

#include "Manager.h"

#include "ECS/Types.h"

#include "Components/Components.h"

#include "Systems/Systems.h"

class Stage
	: public Manager<ECS::Entity>
{
public:
	Stage();
	~Stage();

	void Init();

	void Update();

private:
	Resource::ResourceManager* mResources = nullptr;

	Component::com_Camera mCamera; 

	std::shared_ptr<System::sys_PlayerControl> PlayerSys;
	std::shared_ptr<System::sys_Render> RenderSys;
};

