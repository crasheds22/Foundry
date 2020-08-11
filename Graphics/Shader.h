#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	static unsigned int New(const char* vertex, const char* fragment, const char* geometry = nullptr);

	static void Use(unsigned int shader);

    static void setBool(unsigned int ID, const std::string& name, bool value);
    // ------------------------------------------------------------------------
    static void setInt(unsigned int ID, const std::string& name, int value);
    // ------------------------------------------------------------------------
    static void setFloat(unsigned int ID, const std::string& name, float value);
    // ------------------------------------------------------------------------
    static void setVec2(unsigned int ID, const std::string& name, const glm::vec2& value);
    static void setVec2(unsigned int ID, const std::string& name, float x, float y);
    // ------------------------------------------------------------------------
    static void setVec3(unsigned int ID, const std::string& name, const glm::vec3& value);
    static void setVec3(unsigned int ID, const std::string& name, float x, float y, float z);
    // ------------------------------------------------------------------------
    static void setVec4(unsigned int ID, const std::string& name, const glm::vec4& value);
    static void setVec4(unsigned int ID, const std::string& name, float x, float y, float z, float w);
    // ------------------------------------------------------------------------
    static void setMat2(unsigned int ID, const std::string& name, const glm::mat2& mat);
    // ------------------------------------------------------------------------
    static void setMat3(unsigned int ID, const std::string& name, const glm::mat3& mat);
    // ------------------------------------------------------------------------
    static void setMat4(unsigned int ID, const std::string& name, const glm::mat4& mat);

private:
	Shader() { };

    static void checkCompileErrors(GLuint shader, std::string type);
};

