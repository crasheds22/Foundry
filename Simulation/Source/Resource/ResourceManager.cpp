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

    void ResourceManager::CreateTexture(std::string name, std::string filepath, TextureType type)
    {
        Texture tex(name, filepath.c_str(), type);

        mTextureManager.Create(name, tex);
    }

    void ResourceManager::CreateShader(std::string name, std::string vertex, std::string frag, std::string geo)
    {
        unsigned int sha = ShaderLoader::New(vertex.c_str(), frag.c_str(), geo.length() > 0 ? geo.c_str() : nullptr);

        mShaderManager.Create(name, sha);
    }

    Model* ResourceManager::RetrieveModel(std::string name)
    {
        return mModelManager.Retrieve(name);
    }

    Texture* ResourceManager::RetrieveTexture(std::string name)
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
