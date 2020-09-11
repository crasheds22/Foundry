#include "com_Model.h"

namespace Component
{
	com_Model::com_Model(std::string path) : mModel(Model(path))
	{
	}

	void com_Model::Draw(unsigned int shaderID)
	{
		mModel.Draw(shaderID);
	}
}
