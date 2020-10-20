#include "Resource/ResourceManager.h"

namespace Resource
{
    Resource::ResourceManager::~ResourceManager()
    {
        mModelManager->DeleteAll();
        mModelManager = nullptr;

        mShaderManager->DeleteAll();
        mShaderManager = nullptr;

        mTextureManager->DeleteAll();
        mTextureManager = nullptr;

        mWorldManager->DeleteAll();
        mWorldManager = nullptr;
    }

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

    void ResourceManager::CreateShader(std::string name, const char* vertex, const char* frag, const char* geo)
    {
        if(mShaderManager)
            mShaderManager->Create(name, vertex, frag, geo);
    }

    void ResourceManager::CreateWorld(std::string filepath, std::string name)
    {
        if (mWorldManager)
            mWorldManager->Create(filepath, name);
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

    World* ResourceManager::RetrieveWorld(std::string name)
    {
        if (mWorldManager)
            return mWorldManager->Retrieve(name);

        return nullptr;
    }

    ResourceManager::ResourceManager()
    {
        if (!mModelManager)
            mModelManager = &ModelManager::Instance();
        if (!mTextureManager)
            mTextureManager = &TextureManager::Instance();
        if (!mShaderManager)
            mShaderManager = &ShaderManager::Instance();
        if (!mWorldManager)
            mWorldManager = &WorldManager::Instance();
    }

    void ResourceManager::Init()
    {
        if(!mModelManager)
            mModelManager   = &ModelManager::Instance();
        if(!mTextureManager)
            mTextureManager = &TextureManager::Instance();
        if(!mShaderManager)
            mShaderManager  = &ShaderManager::Instance();
        if (!mWorldManager)
            mWorldManager = &WorldManager::Instance();
    }

}
