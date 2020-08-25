#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    static unsigned int New(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    
    static void Use(unsigned int ID);

    static void setBool (unsigned int ID, const std::string& name, bool value);

    static void setInt  (unsigned int ID, const std::string& name, int value);

    static void setFloat(unsigned int ID, const std::string& name, float value);

    static void setVec2 (unsigned int ID, const std::string& name, const glm::vec2& value);
    static void setVec2 (unsigned int ID, const std::string& name, float x, float y);

    static void setVec3 (unsigned int ID, const std::string& name, const glm::vec3& value);
    static void setVec3 (unsigned int ID, const std::string& name, float x, float y, float z);

    static void setVec4 (unsigned int ID, const std::string& name, const glm::vec4& value);
    static void setVec4 (unsigned int ID, const std::string& name, float x, float y, float z, float w);

    static void setMat2 (unsigned int ID, const std::string& name, const glm::mat2& mat);

    static void setMat3 (unsigned int ID, const std::string& name, const glm::mat3& mat);

    static void setMat4 (unsigned int ID, const std::string& name, const glm::mat4& mat);

    static void DeleteShader(unsigned int ID);

private:
	Shader() { };
    Shader(const Shader& S) { };
    ~Shader() { };

    static void checkCompileErrors(unsigned int shader, std::string type);
};
  