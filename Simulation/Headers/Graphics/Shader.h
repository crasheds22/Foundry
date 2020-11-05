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

/** @class ShaderLoader
 *
 *  @brief Static class to load and compile a shader
 *
 *  @author Aaron Thomson
 */
class ShaderLoader
{
public:
    /** @brief Creates a new shader from the input files and compiles it, returning the program id
     */
    static unsigned int New(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

private:
    /** @brief Helper function to check the compile time errors of the shader
     */
    static void checkCompileErrors(unsigned int shader, std::string type);
};

/** @class Shader
 *
 *  @brief Class used to store the data for and manipulate a shader
 *
 *  @author Aaron Thomson
 */
class Shader
{
public:
    /** @brief Constructor
     *
     *  @param name The name of the shader
     *  @param vertex The path to the vertex shader
     *  @param frag The path to the fragment shader
     *  @param geo The path to the geometry shader
     */
    Shader(const std::string name, const char* vertex, const char* frag, const char* geo = nullptr);

    /** @brief Returns the name of the shader
     */
    std::string Name() const;
    
    /** @brief Returns the ID of the shader program
     */
    unsigned int ID() const;

    /** @brief Tells OpenGL to use the shader
     */
    void Use();

    /** @brief Sets a boolean uniform
     */
    void setBool (const std::string& name, bool value);

    /** @brief Sets an integer uniform value
     */
    void setInt  (const std::string& name, int value);

    /** @brief Sets a float uniform value
     */
    void setFloat(const std::string& name, float value);

    void setVec2 (const std::string& name, const glm::vec2& value);
    void setVec2 (const std::string& name, float x, float y);

    void setVec3 (const std::string& name, const glm::vec3& value);
    void setVec3 (const std::string& name, float x, float y, float z);

    void setVec4 (const std::string& name, const glm::vec4& value);
    void setVec4 (const std::string& name, float x, float y, float z, float w);

    void setMat2 (const std::string& name, const glm::mat2& mat);

    void setMat3 (const std::string& name, const glm::mat3& mat);

    void setMat4 (const std::string& name, const glm::mat4& mat);

    /** @brief Deletes the sahder 
     */
    void DeleteShader();

private:
    unsigned int mID;   /*!< The ID of the shader program */
    std::string mName;  /*!< The name of the shader */
};
  