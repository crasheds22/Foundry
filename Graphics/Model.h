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

#include "Texture.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct ModelTexture
{
	unsigned int ID;
	std::string Type;
	std::string Path;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<ModelTexture> textures);

	void Draw(unsigned int shaderID);

private:
	std::vector<Vertex> mVertices;
	std::vector<unsigned int> mIndices;
	std::vector<ModelTexture> mTextures;

	unsigned int mVAO, mVBO, mEBO;

	void SetUpMesh();
};

class Model
{
public:
	Model(const std::string path);

	void Draw(unsigned int shaderID);

private:
	std::vector<ModelTexture> mTexturesLoaded;
	std::vector<Mesh> mMeshes;
	std::string mDirectory;

	void LoadModel(const std::string path);

	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<ModelTexture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
};

