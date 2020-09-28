#pragma once

#include "Graphics/Graphics.h"
#include "Resource/ResourceManager.h"
#include "Props.h"

#include "Manager.h"
#include "Singleton.h"

#include "Stage.h"

#include "Components/Components.h"

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

	Resource::ResourceManager* mResourceManager;

	Props* mProps;

	Stage mActiveStage;
};

