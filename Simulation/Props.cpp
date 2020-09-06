#include "Props.h"

double Props::mCurrentTime = 0;
double Props::mLastFrame = 0;
double Props::mDeltaTime = 0;

Component::Camera* Props::mActiveCamera = nullptr;

void Props::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void Props::MouseMoveCallback(GLFWwindow* window, double xPos, double yPos)
{
}

void Props::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
}

void Props::ScrollWheelCallback(GLFWwindow* window, double xOff, double yOff)
{
}

void Props::ResizeCallback(GLFWwindow* window, int width, int height)
{
}

void Props::CalcDeltaTime()
{
	mCurrentTime = _Graphics::GetTime();

	mDeltaTime = mCurrentTime - mLastFrame;

	mLastFrame = mCurrentTime;
}

double Props::DeltaTime()
{
	return mDeltaTime;
}

Component::Camera* Props::GetActiveCamera()
{
	return mActiveCamera;
}

void Props::SetActiveCamera(Component::Camera* cam)
{
	mActiveCamera = cam;
}
