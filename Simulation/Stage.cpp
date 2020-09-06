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


}

void Stage::PlayShow()
{

}

void Stage::PackDown()
{

}
