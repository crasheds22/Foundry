#pragma once

#include "Graphics/Graphics.h"
#include "Resource/ResourceManager.h"

#include "Manager.h"
#include "Singleton.h"

#include "Stage.h"

#include "Systems/SystemsManager.h"

class Theatre
	: public Singleton<Theatre>, public Manager<Stage>
{
public:
	Theatre();

	void PreShow();

	void PlayShow();

	void EndShow();

private:
	Graphics* mGraphics;

	SystemsManager* mActiveSystems;

	Resource::ResourceManager* mResourceManager;
};

