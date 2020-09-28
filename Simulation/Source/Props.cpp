#include "Props.h"

void Props::UpdateKeys()
{
    if (mContext)
    {
        for (auto key : mKeys)
            mKeysLast[key.first] = key.second;

            //Movement
        for (auto action : mMoveActionMap)
            mKeys[action.second] = mContext->KeyPressed(action.second);

            //Global actions
        for (auto action : mGlobalActionMap)
            mKeys[action.second] = mContext->KeyPressed(action.second);

            //User actions
        for (auto action : mUserActionMap)
            mKeys[action.second] = mContext->KeyPressed(action.second);
    }
}

void Props::UpdateMouse()
{
    if (mContext)
    {
        mMouseLastPos = mMousePos;

        double X, Y;
        mContext->MousePos(X, Y);

        mMousePos = std::pair<double, double>(X, Y);
    }
}

void Props::UpdateDT()
{
    if (mContext)
    {
        float currentFrame = mContext->GetTime();
        mDeltaTime = currentFrame - mLastFrame;
        mLastFrame = currentFrame;
    }
}

bool Props::Pressed(Actions::Move action)
{
    return mKeys[mMoveActionMap[action]];
}

bool Props::Pressed(Actions::User action)
{
    return mKeys[mUserActionMap[action]];
}

bool Props::Pressed(Actions::Global action)
{
    return mKeys[mGlobalActionMap[action]];
}

bool Props::Released(Actions::Move action)
{
    return !mKeys[mMoveActionMap[action]];
}

bool Props::Released(Actions::User action)
{
    return !mKeys[mUserActionMap[action]];
}

bool Props::Released(Actions::Global action)
{
    return !mKeys[mGlobalActionMap[action]];
}

bool Props::JustReleased(Actions::Move action)
{
    return mKeys[mMoveActionMap[action]] != mKeysLast[mMoveActionMap[action]];
}

bool Props::JustReleased(Actions::User action)
{
    return mKeys[mUserActionMap[action]] != mKeysLast[mUserActionMap[action]];
}

bool Props::JustReleased(Actions::Global action)
{
    return mKeys[mGlobalActionMap[action]] != mKeysLast[mGlobalActionMap[action]];
}

std::pair<double, double> Props::MouseOffset()
{
    double xOff = mMousePos.first - mMouseLastPos.first;
    double yOff = mMouseLastPos.second - mMousePos.second;

    return std::pair<double, double>(xOff, yOff);
}

std::pair<double, double> Props::ThisMouse()
{
    return mMousePos;
}

std::pair<double, double> Props::LastMouse()
{
    return mMouseLastPos;
}

float Props::DeltaTime() const
{
    return mDeltaTime;
}

Props::Props()
{
    mContext = &Graphics::Instance();

    mMoveActionMap =
    {
        { Actions::Move::FORWARD, GLFW_KEY_W },
        { Actions::Move::BACKWARD, GLFW_KEY_S },
        { Actions::Move::LEFT, GLFW_KEY_A },
        { Actions::Move::RIGHT, GLFW_KEY_D }
    };

    mUserActionMap =
    {
        { Actions::User::USE, GLFW_KEY_E }
    };

    mGlobalActionMap =
    {
        { Actions::Global::QUIT, GLFW_KEY_ESCAPE }
    };

    mMousePos = { 0.0, 0.0 };
    mMouseLastPos = { 0.0, 0.0 };

    mKeys =
    {
        { GLFW_KEY_A, false },
        { GLFW_KEY_D, false },
        { GLFW_KEY_E, false },
        { GLFW_KEY_S, false },
        { GLFW_KEY_W, false },
        { GLFW_KEY_ESCAPE, false }
    };

    mKeysLast = mKeys;
}
