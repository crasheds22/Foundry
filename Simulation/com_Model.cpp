#include "com_Model.h"

namespace Component
{
	com_Model::com_Model(std::string path) : mMeshes(Model::Instance().New(path))
	{
	}

	com_Model::com_Model(const com_Model& m)
	{
		for (const auto& mesh : m.mMeshes)
		{
			mMeshes.push_back(mesh);
		}
	}

	void com_Model::Draw(unsigned int shaderID) const
	{
		for (auto mesh : mMeshes)
			mesh.Draw(shaderID);
	}
}
