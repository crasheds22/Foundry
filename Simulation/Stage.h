#pragma once

#include "../ECS_core/Coordinator.h"

#include "com_Camera.h"
#include "com_Model.h"
#include "com_Player.h"
#include "com_Shader.h"
#include "com_Transform.h"

#include "sys_Render.h"

#include <memory>
#include <vector>

class Stage
{
public:
	Stage();
	~Stage();

	void Init();

	void PlayShow();

private:
	void PackDown();

	bool mInitialised;

	ECS::Coordinator mCoordinator;

	std::shared_ptr<System::Render> mRenderSystem;

	std::vector<ECS::Entity> mStageEntities;
};

