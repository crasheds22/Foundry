#pragma once
#include "UnitTest.h"

#include "Resource/ResourceManager.h"    

class ResourceManagerTest :
    public UnitTest
{
public:
    ResourceManagerTest() : UnitTest("ResourceManagement") { ResMgr = &Resource::ResourceManager::Instance(); }

    bool Test() override;

private:
    bool ShaderTesting();
    bool TextureTesting();
    bool ModelTesting();


    Resource::ResourceManager* ResMgr = nullptr;
};

