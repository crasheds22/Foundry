#pragma once

#include "Resource/ResourceManager.h"
#include "Systems/SystemsManager.h"

#include "Manager.h"

#include "ECS/Types.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

#include "Components/Components.h"

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

	SystemsManager* mSystems = nullptr;

};

