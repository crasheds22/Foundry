#include "Components/com_Shader.h"

namespace Component
{
	com_Shader::com_Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	{
		mID = ShaderLoader::New(vertexPath, fragmentPath, geometryPath);
	}

	unsigned int com_Shader::ID() const
	{
		return mID;
	}

	void com_Shader::Use()
	{
		ShaderLoader::Use(mID);
	}

	void com_Shader::setBool(const std::string& name, bool value)
	{
		ShaderLoader::setBool(mID, name, value);
	}

	void com_Shader::setInt(const std::string& name, int value)
	{
		ShaderLoader::setInt(mID, name, value);
	}

	void com_Shader::setFloat(const std::string& name, float value)
	{
		ShaderLoader::setFloat(mID, name, value);
	}

	void com_Shader::setVec2(const std::string& name, const glm::vec2& value)
	{
		ShaderLoader::setVec2(mID, name, value);
	}
	void com_Shader::setVec2(const std::string& name, float x, float y)
	{
		ShaderLoader::setVec2(mID, name, x, y);
	}

	void com_Shader::setVec3(const std::string& name, const glm::vec3& value)
	{
		ShaderLoader::setVec3(mID, name, value);
	}
	void com_Shader::setVec3(const std::string& name, float x, float y, float z)
	{
		ShaderLoader::setVec3(mID, name, x, y, z);
	}

	void com_Shader::setVec4(const std::string& name, const glm::vec4& value)
	{
		ShaderLoader::setVec4(mID, name, value);
	}
	void com_Shader::setVec4(const std::string& name, float x, float y, float z, float w)
	{
		ShaderLoader::setVec4(mID, name, x, y, z, w);
	}

	void com_Shader::setMat2(const std::string& name, const glm::mat2& mat)
	{
		ShaderLoader::setMat2(mID, name, mat);
	}

	void com_Shader::setMat3(const std::string& name, const glm::mat3& mat)
	{
		ShaderLoader::setMat3(mID, name, mat);
	}

	void com_Shader::setMat4(const std::string& name, const glm::mat4& mat)
	{
		ShaderLoader::setMat4(mID, name, mat);
	}
}
