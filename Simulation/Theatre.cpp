#include "Theatre.h"

Theatre::Theatre() : mInitialised(false)
{
    Init();
}

Theatre::~Theatre()
{
    Shutdown();
}

void Theatre::Init()
{
    if (mInitialised)
        Shutdown();

    _Graphics::InitializeGLFW();

    mWindow = _Graphics::CreateWindow("Simulation");

    _Graphics::MakeWindowCurrent(mWindow);

    _Graphics::SetResizeCallback(mWindow, Props::ResizeCallback);
    _Graphics::SetCursorCallback(mWindow, Props::MouseMoveCallback);
    _Graphics::SetMouseButtonCallback(mWindow, Props::MouseButtonCallback);
    _Graphics::SetScrollCallback(mWindow, Props::ScrollWheelCallback);
    _Graphics::SetKeyboardCallback(mWindow, Props::KeyboardCallback);

    _Graphics::CaptureMouse(mWindow);

    _Graphics::InitializeGLAD();

    _Graphics::Enable(_Graphics::Capability::DEPTH);

    mInitialised = true;
}

void Theatre::PlayShows()
{
    while (!_Graphics::ShouldWindowClose(mWindow))
    {
        Props::DeltaTime();

        _Graphics::Clear();

        mStageOne.PlayShow();

        _Graphics::SwapBuffers(mWindow);
        _Graphics::PollForEvents();
    }
}

bool Theatre::Shutdown()
{
    _Graphics::Terminate();

    return true;
}
