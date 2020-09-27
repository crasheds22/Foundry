#include "Resource/ResourceManager.h"

namespace Resource
{
    void ResourceManager::CreateModel(std::string filepath, std::string name)
    {
        if(mModelManager)
            mModelManager->Create(filepath.c_str(), name);
    }

    void ResourceManager::CreateTexture(std::string name, std::string filepath, TextureType type)
    {
        if(mTextureManager)
            mTextureManager->Create(filepath.c_str(), type, name);
    }

    void ResourceManager::CreateShader(std::string name, std::string vertex, std::string frag, std::string geo)
    {
        if(mShaderManager)
            mShaderManager->Create(name, vertex.c_str(), frag.c_str(), geo.c_str());
    }

    Model* ResourceManager::RetrieveModel(std::string name)
    {
        if(mModelManager)
            return mModelManager->Retrieve(name);

        return nullptr;
    }

    Texture* ResourceManager::RetrieveTexture(std::string name)
    {
        if(mTextureManager)
            return mTextureManager->Retrieve(name);

        return nullptr;
    }

    Shader* ResourceManager::RetrieveShader(std::string name)
    {
        if(mShaderManager)
            return mShaderManager->Retrieve(name);

        return nullptr;
    }

    void ResourceManager::Init()
    {
        if(!mModelManager)
            mModelManager   = &ModelManager::Instance();
        if(!mTextureManager)
            mTextureManager = &TextureManager::Instance();
        if(!mShaderManager)
            mShaderManager  = &ShaderManager::Instance();
    }

}
