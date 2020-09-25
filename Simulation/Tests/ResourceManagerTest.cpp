#include "ResourceManagerTest.h"

bool ResourceManagerTest::Test()
{
	bool allPassed = false;

	allPassed = ShaderTesting();
	allPassed = TextureTesting();
	allPassed = ModelTesting();

	return allPassed;
}

bool ResourceManagerTest::ShaderTesting()
{
	return false;
}

bool ResourceManagerTest::TextureTesting()
{


	return false;
}

bool ResourceManagerTest::ModelTesting()
{
	return false;
}
