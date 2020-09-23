#include "Resource/ResourceManager.h"

namespace Resource
{
    ResourceManager& ResourceManager::Instance()
    {
        static ResourceManager mInstance;

        return mInstance;
    }

    void ResourceManager::CreateModel(std::string name, std::string filepath)
    {
        Model temp(filepath);

        mModelManager.Create(name, temp);
    }

    void ResourceManager::CreateTexture(std::string name, std::string filepath)
    {
        unsigned int tex = TextureLoader::New(filepath.c_str());

        mTextureManager.Create(name, tex);
    }

    void ResourceManager::CreateShader(std::string name, std::string vertex, std::string frag, std::string geo)
    {
        unsigned int sha = Shader::New(vertex.c_str(), frag.c_str(), geo.length() > 0 ? geo.c_str() : nullptr);

        mShaderManager.Create(name, sha);
    }

    Model* ResourceManager::RetrieveModel(std::string name)
    {
        return mModelManager.Retrieve(name);
    }

    unsigned int* ResourceManager::RetrieveTexture(std::string name)
    {
        return mTextureManager.Retrieve(name);
    }

    unsigned int* ResourceManager::RetrieveShader(std::string name)
    {
        return mShaderManager.Retrieve(name);
    }

    ResourceManager::ResourceManager()
    {

    }

}