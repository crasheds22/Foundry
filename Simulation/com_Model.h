#pragma once

#include <string>
#include <vector>

#include "../Graphics/Model.h"

namespace Component
{
	class com_Model
	{
	public:
		com_Model() {};
		com_Model(std::string path);
		com_Model(const com_Model& m);

		void Draw(unsigned int shaderID);

	private:
		std::vector<Mesh> mMeshes;
	};
}
