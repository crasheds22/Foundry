#pragma once

#include "Manager.h"
#include "Singleton.h"

#include "Graphics/Shader.h"

namespace Resource
{
	class ShaderManager
		: public Manager<Shader>, public Singleton
	{
	public:

	private:
	};
}
