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


}

void Theatre::PlayShows()
{
    do
    {

    } while (true);
}

bool Theatre::Shutdown()
{
    return false;
}
