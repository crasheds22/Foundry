#pragma once

#include "Graphics/Graphics.h"
#include "Resource/ResourceManager.h"
#include "Props.h"

#include "Manager.h"
#include "Singleton.h"

#include "Stage.h"

#include "Systems/SystemsManager.h"

#include "ECS/Coordinator.h"
ECS::Coordinator gCoordinator;

#include "Components/Components.h"
#include "Systems/Systems.h"

class Theatre
	: public Singleton<Theatre>
{
public:
	Theatre();
	~Theatre();

	void PreShow();

	void PlayShow();

	void EndShow();

private:
	Graphics* mGraphics;

	SystemsManager* mActiveSystems;

	Resource::ResourceManager* mResourceManager;

	Props* mProps;

	Stage mActiveStage;
};

