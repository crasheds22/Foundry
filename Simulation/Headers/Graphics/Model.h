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

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures);

	void Draw(unsigned int shaderID);

private:
	std::vector<Vertex> mVertices;
	std::vector<unsigned int> mIndices;
	std::vector<Texture*> mTextures;

	unsigned int mVAO, mVBO, mEBO;

	void SetUpMesh();
};

class Model
{
public:
	Model() {};
	Model(const std::string path, std::string name = "");

	std::string Name() const;

	void Draw(unsigned int shaderID);

protected:
	std::vector<Mesh> mMeshes;
	std::string mName;
};

class World : public Model
{
public:
	World(const std::string path, std::string name = "");

	std::map<std::string, std::vector<std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>>>> SpawnPoints() const;

private:
	std::map<std::string, std::vector<std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>>>> mSpawns;

};

class ModelLoader
{
public:
	static void New(const std::string path, std::vector<Mesh>& meshes);
	static void NewWorld(const std::string path, std::vector<Mesh>& meshes, std::map<std::string, std::vector<std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>>>>& spawns);

	static std::string CurrentDirectory;

private:
	static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes);
	static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	static std::vector<Texture*> LoadMaterialTextures(aiMaterial* material, aiTextureType type, TextureType typeName);

	static void ProcessWorldNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, std::map<std::string, std::vector<std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>>>>& spawns);
	static std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>> ProcessSpawnMesh(aiMesh* mesh, const aiScene* scene);

};
