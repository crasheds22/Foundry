#include "com_Shader.h"

#include "../Graphics/Shader.h"
using StaticShader = Shader;

namespace Component
{
	Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	{
		mID = StaticShader::New(vertexPath, fragmentPath, geometryPath);
	}

	Shader::~Shader()
	{
		StaticShader::DeleteShader(mID);
	}

	unsigned int Shader::ID() const
	{
		return mID;
	}

	void Shader::Use()
	{
		StaticShader::Use(mID);
	}

	void Shader::setBool(const std::string& name, bool value)
	{
		StaticShader::setBool(mID, name, value);
	}

	void Shader::setInt(const std::string& name, int value)
	{
		StaticShader::setInt(mID, name, value);
	}

	void Shader::setFloat(const std::string& name, float value)
	{
		StaticShader::setFloat(mID, name, value);
	}

	void Shader::setVec2(const std::string& name, const glm::vec2& value)
	{
		StaticShader::setVec2(mID, name, value);
	}
	void Shader::setVec2(const std::string& name, float x, float y)
	{
		StaticShader::setVec2(mID, name, x, y);
	}

	void Shader::setVec3(const std::string& name, const glm::vec3& value)
	{
		StaticShader::setVec3(mID, name, value);
	}
	void Shader::setVec3(const std::string& name, float x, float y, float z)
	{
		StaticShader::setVec3(mID, name, x, y, z);
	}

	void Shader::setVec4(const std::string& name, const glm::vec4& value)
	{
		StaticShader::setVec4(mID, name, value);
	}
	void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
	{
		StaticShader::setVec4(mID, name, x, y, z, w);
	}

	void Shader::setMat2(const std::string& name, const glm::mat2& mat)
	{
		StaticShader::setMat2(mID, name, mat);
	}

	void Shader::setMat3(const std::string& name, const glm::mat3& mat)
	{
		StaticShader::setMat3(mID, name, mat);
	}

	void Shader::setMat4(const std::string& name, const glm::mat4& mat)
	{
		StaticShader::setMat4(mID, name, mat);
	}
}
