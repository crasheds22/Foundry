#include "Graphics/Model.h"

std::string FullName(TextureType type)
{
	switch (type)
	{
	case TextureType::DIFFUSE:
		return "texture_diffuse";
	case TextureType::AMBIENT:
		return "teture_ambient";
	case TextureType::HEIGHT:
		return "texture_height";
	case TextureType::NORMAL:
		return "texture_normal";
	case TextureType::SPECULAR:
		return "texture_specular";
	default:
		return "";
	}
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures)
{
	mVertices = vertices;
	mIndices = indices;
	mTextures = textures;

	SetUpMesh();
}

void Mesh::Draw(unsigned int shaderID)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (unsigned int i = 0; i < mTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name = FullName(mTextures[i]->Type());
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		else if (name == "texture_normal")
			number = std::to_string(normalNr++);
		else if (name == "texture_height")
			number = std::to_string(heightNr++);

		glUniform1i(glGetUniformLocation(shaderID, (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, mTextures[i]->ID());
	}

	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::SetUpMesh()
{
	// create buffers/arrays
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);

	glBindVertexArray(mVAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}

Model::Model(const std::string path, std::string name)
{
	if (name.length() > 0)
		mName = name;
	else
		mName = path.substr(path.find_last_of('/') + 1, path.find_last_of('.') - path.find_last_of('/') - 1);

	ModelLoader::New(path, mMeshes);
}

std::string Model::Name() const
{
	return mName;
}

void Model::Draw(unsigned int shaderID)
{
	for (auto& mesh : mMeshes)
	{
		mesh.Draw(shaderID);
	}
}

std::string ModelLoader::CurrentDirectory = "";

void ModelLoader::New(const std::string path, std::vector<Mesh>& meshes)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		exit(1);
	}

	CurrentDirectory = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene, meshes);
}

void ModelLoader::NewWorld(const std::string path, std::vector<Mesh>& meshes, std::map<std::string, std::vector<std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>>>>& spawns)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		exit(1);
	}

	CurrentDirectory = path.substr(0, path.find_last_of('/'));

	ProcessWorldNode(scene->mRootNode, scene, meshes, spawns);
}

void ModelLoader::ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene, meshes);
	}
}

Mesh ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture*> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		// normals
		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}
		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
			// tangent
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.Tangent = vector;
			// bitangent
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.Bitangent = vector;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	std::vector<Texture*> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	std::vector<Texture*> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::SPECULAR);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<Texture*> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, TextureType::NORMAL);
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<Texture*> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, TextureType::HEIGHT);
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}

std::vector<Texture*> ModelLoader::LoadMaterialTextures(aiMaterial* material, aiTextureType type, TextureType typeName)
{
	std::vector<Texture*> textures;
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);

		std::string filePath = CurrentDirectory + "/" + str.C_Str();
		std::string name = filePath.substr(filePath.find_last_of('/'), filePath.find_last_of('.'));

		if (Resource::TextureManager::Instance().Find(name))
		{
			textures.push_back(Resource::TextureManager::Instance().Retrieve(name));
		}
		else
		{
			Resource::TextureManager::Instance().Create(filePath, typeName);

			textures.push_back(Resource::TextureManager::Instance().Retrieve(name));
		}
	}
	return textures;
}

void ModelLoader::ProcessWorldNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes, std::map<std::string, std::vector<std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>>>>& spawns)
{
	std::string nodeName = node->mName.C_Str();

	if (nodeName.find("spawn") != std::string::npos)
	{
		std::string objName = nodeName.substr(nodeName.find_first_of('_') + 1, nodeName.find_last_of('_') - nodeName.find_first_of('_') - 1);

		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			spawns[objName].push_back(ProcessSpawnMesh(scene->mMeshes[node->mMeshes[i]], scene));
		}
	}
	else
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(ProcessMesh(mesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessWorldNode(node->mChildren[i], scene, meshes, spawns);
		}
	}
}

std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>> ModelLoader::ProcessSpawnMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<glm::vec3> positions;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		glm::vec3 pos(0);

		pos.x = mesh->mVertices[i].x;
		pos.y = mesh->mVertices[i].y;
		pos.z = mesh->mVertices[i].z;

		positions.push_back(pos);
	}

	glm::vec3 worldPos(0), min(0.0f), max(0.0f);

	for (int i = 0; i < positions.size(); i++)
	{
		worldPos += positions[i];

		if (positions[i].x < min.x)
			min.x = positions[i].x;
		
		if (positions[i].x > max.x)
			max.x = positions[i].x;

		if (positions[i].y < min.y)
			min.y = positions[i].y;
		
		if (positions[i].y > max.y)
			max.y = positions[i].y;

		if (positions[i].z < min.z)
			min.z = positions[i].z;
		
		if (positions[i].z > max.z)
			max.z = positions[i].z;
	}

	worldPos = glm::vec3(worldPos.x / positions.size(), worldPos.y / positions.size(), worldPos.z / positions.size());

	max = max - worldPos;
	min = min - worldPos;

	return std::make_pair(worldPos, std::make_pair(max, min));
}

World::World(const std::string path, std::string name)
{
	if (name.length() > 0)
		mName = name;
	else
		mName = path.substr(path.find_last_of('/') + 1, path.find_last_of('.') - path.find_last_of('/') - 1);

	ModelLoader::NewWorld(path, mMeshes, mSpawns);
}

std::map<std::string, std::vector<std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>>>> World::SpawnPoints() const
{
	return mSpawns;
}
