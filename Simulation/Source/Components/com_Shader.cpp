#include "Components/com_Shader.h"

namespace Component
{
	com_Shader::com_Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	{
		mID = Shader::New(vertexPath, fragmentPath, geometryPath);
	}

	unsigned int com_Shader::ID() const
	{
		return mID;
	}

	void com_Shader::Use()
	{
		Shader::Use(mID);
	}

	void com_Shader::setBool(const std::string& name, bool value)
	{
		Shader::setBool(mID, name, value);
	}

	void com_Shader::setInt(const std::string& name, int value)
	{
		Shader::setInt(mID, name, value);
	}

	void com_Shader::setFloat(const std::string& name, float value)
	{
		Shader::setFloat(mID, name, value);
	}

	void com_Shader::setVec2(const std::string& name, const glm::vec2& value)
	{
		Shader::setVec2(mID, name, value);
	}
	void com_Shader::setVec2(const std::string& name, float x, float y)
	{
		Shader::setVec2(mID, name, x, y);
	}

	void com_Shader::setVec3(const std::string& name, const glm::vec3& value)
	{
		Shader::setVec3(mID, name, value);
	}
	void com_Shader::setVec3(const std::string& name, float x, float y, float z)
	{
		Shader::setVec3(mID, name, x, y, z);
	}

	void com_Shader::setVec4(const std::string& name, const glm::vec4& value)
	{
		Shader::setVec4(mID, name, value);
	}
	void com_Shader::setVec4(const std::string& name, float x, float y, float z, float w)
	{
		Shader::setVec4(mID, name, x, y, z, w);
	}

	void com_Shader::setMat2(const std::string& name, const glm::mat2& mat)
	{
		Shader::setMat2(mID, name, mat);
	}

	void com_Shader::setMat3(const std::string& name, const glm::mat3& mat)
	{
		Shader::setMat3(mID, name, mat);
	}

	void com_Shader::setMat4(const std::string& name, const glm::mat4& mat)
	{
		Shader::setMat4(mID, name, mat);
	}
}
