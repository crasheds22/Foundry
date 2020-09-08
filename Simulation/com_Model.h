#pragma once

#include <string>
#include <vector>

#include "../Graphics/Model.h"

namespace Component
{
	class Model
	{
	public:
		Model() {};
		Model(std::string path);
		Model(const Model& m);
		~Model();

		void Draw(unsigned int shaderID);

	private:
		std::vector<Mesh> mMeshes{};
	};
}
