#include "Components/com_Shader.h"

namespace Component
{
	com_Shader::com_Shader(std::string name, const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	{
		Resource::ResourceManager::Instance().CreateShader(name, vertexPath, fragmentPath, geometryPath ? geometryPath : "");

		mShader = Resource::ResourceManager::Instance().RetrieveShader(name);
	}

	com_Shader::com_Shader(std::string name)
	{
		mShader = Resource::ResourceManager::Instance().RetrieveShader(name);
	}

	unsigned int com_Shader::ID() const
	{
		return mShader->ID();
	}

	void com_Shader::Use()
	{
		mShader->Use();
	}

	void com_Shader::setBool(const std::string& name, bool value)
	{
		mShader->setBool(name, value);
	}

	void com_Shader::setInt(const std::string& name, int value)
	{
		mShader->setInt( name, value);
	}

	void com_Shader::setFloat(const std::string& name, float value)
	{
		mShader->setFloat( name, value);
	}

	void com_Shader::setVec2(const std::string& name, const glm::vec2& value)
	{
		mShader->setVec2( name, value);
	}
	void com_Shader::setVec2(const std::string& name, float x, float y)
	{
		mShader->setVec2( name, x, y);
	}

	void com_Shader::setVec3(const std::string& name, const glm::vec3& value)
	{
		mShader->setVec3( name, value);
	}
	void com_Shader::setVec3(const std::string& name, float x, float y, float z)
	{
		mShader->setVec3( name, x, y, z);
	}

	void com_Shader::setVec4(const std::string& name, const glm::vec4& value)
	{
		mShader->setVec4( name, value);
	}
	void com_Shader::setVec4(const std::string& name, float x, float y, float z, float w)
	{
		mShader->setVec4( name, x, y, z, w);
	}

	void com_Shader::setMat2(const std::string& name, const glm::mat2& mat)
	{
		mShader->setMat2( name, mat);
	}

	void com_Shader::setMat3(const std::string& name, const glm::mat3& mat)
	{
		mShader->setMat3( name, mat);
	}

	void com_Shader::setMat4(const std::string& name, const glm::mat4& mat)
	{
		mShader->setMat4( name, mat);
	}
}
