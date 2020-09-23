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
    bool TextureTesting();


    Resource::ResourceManager* ResMgr = nullptr;
};

