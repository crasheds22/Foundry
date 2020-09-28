#pragma once

#include "Singleton.h"
#include "Manager.h"

#include <memory>

#include "ECS/System.h"

class SystemsManager
	: public Singleton<SystemsManager>
	, public Manager<std::shared_ptr<ECS::System>>
{
public:

private:

};
