#pragma once

#include "Stage.h"
#include "Props.h"

#include "../Graphics/Graphics.h"

class Theatre
{
public:
	Theatre();
	~Theatre();

	void Init();

	void PlayShows();

private:
	bool Shutdown();

	bool mInitialised;
	Stage mStageOne;

	GLFWwindow* mWindow;
};

