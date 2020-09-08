#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <string>

namespace Component
{
	class Shader
	{
	public:
		Shader() {};
		Shader(const Shader& s) {};
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		~Shader();

		unsigned int ID() const;

		void Use();

		void setBool(const std::string& name, bool value);

		void setInt(const std::string& name, int value);

		void setFloat(const std::string& name, float value);

		void setVec2(const std::string& name, const glm::vec2& value);
		void setVec2(const std::string& name, float x, float y);

		void setVec3(const std::string& name, const glm::vec3& value);
		void setVec3(const std::string& name, float x, float y, float z);

		void setVec4(const std::string& name, const glm::vec4& value);
		void setVec4(const std::string& name, float x, float y, float z, float w);

		void setMat2(const std::string& name, const glm::mat2& mat);

		void setMat3(const std::string& name, const glm::mat3& mat);

		void setMat4(const std::string& name, const glm::mat4& mat);

	private:
		unsigned int mID{};
	};
}
