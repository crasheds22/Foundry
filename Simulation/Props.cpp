#include "Props.h"

double Props::mCurrentTime = 0;
double Props::mLastFrame = 0;
double Props::mDeltaTime = 0;

Component::Camera* Props::mActiveCamera = nullptr;

std::map<int, bool> Props::mKeyUp;
std::map<int, bool> Props::mKeyDown;

std::map<Action, int> Props::mKeyBind
{
	{Action::LEFT,		GLFW_KEY_A},
	{Action::RIGHT,		GLFW_KEY_D},
	{Action::FORWARD,	GLFW_KEY_W},
	{Action::BACKWARD,	GLFW_KEY_S}
};

std::map<int, bool> Props::mMouseButtonDown;
std::map<int, bool> Props::mMouseButtonUp;

std::map<Action, int> Props::mMouseButtonBind;

bool Props::mFirstMouse = true;

double Props::mLastMouseX = 0.0;
double Props::mLastMouseY = 0.0;
double Props::mMouseOffsetX = 0.0;
double Props::mMouseOffsetY = 0.0;

void Props::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		mKeyDown[key] = true;
		mKeyUp[key] = false;
	}

	if (action == GLFW_RELEASE)
	{
		mKeyDown[key] = false;
		mKeyUp[key] = true;
	}
}

void Props::MouseMoveCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (mFirstMouse)
	{
		mLastMouseX = xPos;
		mLastMouseY = yPos;
		mFirstMouse = false;
	}

	mMouseOffsetX = xPos - mLastMouseX;
	mMouseOffsetY = mLastMouseY - yPos;
}

void Props::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		mMouseButtonDown[button] = true;
		mMouseButtonUp[button] = false;
	}

	if (action == GLFW_RELEASE)
	{
		mMouseButtonDown[button] = false;
		mMouseButtonUp[button] = true;
	}
}

void Props::ScrollWheelCallback(GLFWwindow* window, double xOff, double yOff)
{
}

void Props::ResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
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

bool Props::KeyDown(Action key)
{
	return mKeyDown[mKeyBind[key]];
}

bool Props::KeyHeld(Action key)
{
	return mKeyDown[mKeyBind[key]];
}

bool Props::KeyUp(Action key)
{
	return mKeyUp[mKeyBind[key]];
}

bool Props::MouseButtonDown()
{
	return false;
}

bool Props::MouseButtonHeld()
{
	return false;
}

bool Props::MouseButtonUp()
{
	return false;
}

double Props::MouseOffsetX()
{
	return mMouseOffsetX;
}

double Props::MouseOffsetY()
{
	return mMouseOffsetY;
}
