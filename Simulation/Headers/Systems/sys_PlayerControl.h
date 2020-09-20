#pragma once

#include "ECS/System.h"

#include "Props.h"

namespace System
{
	class sys_PlayerControl
		: public ECS::System
	{
	public:
		void Init();

		void Update();

	private:

};
}
