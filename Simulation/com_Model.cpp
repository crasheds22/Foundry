#include "com_Model.h"

using StaticModel = Model;

namespace Component
{
	Model::Model(std::string path) : mMeshes(StaticModel::New(path))
	{
	}

	Model::Model(const Model& m)
	{
		for (const auto& mesh : m.mMeshes)
		{
			mMeshes.push_back(mesh);
		}
	}

	void Model::Draw(unsigned int shaderID)
	{
		for (auto& mesh : mMeshes)
			mesh.Draw(shaderID);
	}
}
