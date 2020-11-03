#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
#include <iostream>
#include <utility>

#include "Resource/TextureManager.h"

/** @struct Vertex 
 *
 *	@brief Holds data related to an object vertex
 * 
 *	@author Aaron Thomson
 */
struct Vertex
{
	glm::vec3 Position;		/*<! The position of the vertex */
	glm::vec3 Normal;		/*<! The normal of the vertex */
	glm::vec2 TexCoords;	/*<! Texture coordinates for the vertex */
	glm::vec3 Tangent;		/*<! Tangent to the vertex */
	glm::vec3 Bitangent;	/*<! Bitangent to the vertex */
};

/** @class Mesh
 *
 *	@brief Holds information related to an entire mesh of a model
 *
 *	@author Aaron Thomson
 */
class Mesh
{
public:
	/** @brief Constructor
	 *
	 *	@param vertices The vertex points of the the mesh being created
	 *	@param indices	The indices of the mesh
	 *	@param textures	Textures required to paint the mesh
	 */
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures);

	/** @brief Draws the mesh
	 *
	 *	@param shaderID The shader program ID to render with
	 */
	void Draw(unsigned int shaderID);

private:
	std::vector<Vertex> mVertices;		/*<! Vertices in the mesh */
	std::vector<unsigned int> mIndices;	/*<! Indices of the mesh */
	std::vector<Texture*> mTextures;	/*<! Texture pointers of the mesh */

	unsigned int mVAO, mVBO, mEBO;	/*<! Vertex array, vertex buffer and element buffer */

	/** @brief Creates the mesh
	 */
	void SetUpMesh();
};

/** @class Model
 *
 *	@brief Holds all information related to an entire model
 *
 *	@author Aaron Thomson
 */
class Model
{
public:
	/** @brief Constructor
	 */
	Model() {};
	
	/** @brief Constructor
	 *
	 *	@param path The path to the model
	 *	@param name The name of the model
	 */
	Model(const std::string path, std::string name = "");

	/** @brief Returns the name of fthe model
	 */
	std::string Name() const;

	/** @brief Draws the model
	 *
	 *	@param shaderID The ID of the shader program to draw to
	 */
	void Draw(unsigned int shaderID);

protected:
	std::vector<Mesh> mMeshes;	/*!< A list of meshes in the model */
	std::string mName;			/*!< The name of the model */
};

/** @class World
 *
 *	@brief A model that has spawn points for other models
 *
 *	@author Aaron Thomson
 */
class World : public Model
{
public:
	/** @brief Constructor
	 *
	 *	@param path The path to the model
	 *	@param name The name of the model
	 */
	World(const std::string path, std::string name = "");

	/** @brief Returns the map of spawn points in the world 
	 */
	std::map<std::string, std::vector<std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>>>> SpawnPoints() const;

private:
	std::map<std::string, std::vector<std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>>>> mSpawns;	/*<! The mapping of spawn points in the world */

};

/** @class ModelLoader
 *
 *	@brief Static class to load models
 *
 *	@author Aaron Thomson
 */
class ModelLoader
{
public:
	/** @brief Creates a new model
	 *
	 *	@param path The path to the model
	 *	@param meshes A reference to the meshes to write to
	 */
	static void New(const std::string path, std::vector<Mesh>& meshes);
	
	/** @brief Creates a new world model
	 *
	 *	@param path The path to the model
	 *	@param meshes A reference to the meshes to write to
	 *	@param spawns A reference to the spawn pont structure to write to
	 */
	static void NewWorld(const std::string path, std::vector<Mesh>& meshes, std::map<std::string, std::vector<std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>>>>& spawns);

	static std::string CurrentDirectory;	/*!< The path to the current directory */

private:
	/** @brief Processes the current assimp node 
	 */
	static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes);
	
	/** @brief Processes the current assimp mesh
	 */
	static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	
	/** @brief Loads a material texture for the mesh
	 */
	static std::vector<Texture*> LoadMaterialTextures(aiMaterial* material, aiTextureType type, TextureType typeName);

	/** @brief Processes a node for a world model
	 */
	static void ProcessWorldNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, std::map<std::string, std::vector<std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>>>>& spawns);
	
	/** @brief Process a world node, creating a spwan point
	 */
	static std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>> ProcessSpawnMesh(aiMesh* mesh, const aiScene* scene);

};
