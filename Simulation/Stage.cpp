#include "Stage.h"

Stage::Stage() : mInitialised(false)
{
	Init();
}

Stage::~Stage()
{
	PackDown();
}

void Stage::Init()
{
	if (mInitialised)
		PackDown();

	mCoordinator.Init();

	mCoordinator.RegisterComponent<Component::Camera>();
	mCoordinator.RegisterComponent<Component::Model>();
	mCoordinator.RegisterComponent<Component::Player>();
	mCoordinator.RegisterComponent<Component::Shader>();
	mCoordinator.RegisterComponent<Component::Transform>();

	mRenderSystem = mCoordinator.RegisterSystem<System::Render>();
	{
		ECS::Signature sig;
		sig.set(mCoordinator.GetComponentType<Component::Model>());
		sig.set(mCoordinator.GetComponentType<Component::Shader>());
		sig.set(mCoordinator.GetComponentType<Component::Transform>());
		mCoordinator.SetSystemSignature<System::Render>(sig);
	}


}

void Stage::PlayShow()
{
	mRenderSystem->Update();
}

void Stage::PackDown()
{

}
