#pragma once

#include <string>
#include <vector>

#include "Model.h"

namespace Component
{
	class com_Model
	{
	public:
		com_Model() {};
		com_Model(std::string path);

		void Draw(unsigned int shaderID);

	private:
		Model mModel;
	};
}
