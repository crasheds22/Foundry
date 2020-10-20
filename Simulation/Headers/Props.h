#pragma once

#include <map>
#include <utility>

#include "Actions.h"
#include "Graphics/Graphics.h"
#include "Singleton.h"

class Props
	: public Singleton<Props>
{
public:
	Props();

	void UpdateKeys();
	void UpdateMouse();
	void UpdateDT();

	bool Pressed(Actions::Move action);
	bool Pressed(Actions::User action);
	bool Pressed(Actions::Global action);

	bool Released(Actions::Move action);
	bool Released(Actions::User action);
	bool Released(Actions::Global action);

	bool JustReleased(Actions::Move action);
	bool JustReleased(Actions::User action);
	bool JustReleased(Actions::Global action);

	std::pair<double, double> MouseOffset();
	std::pair<double, double> ThisMouse();
	std::pair<double, double> LastMouse();

	float DeltaTime() const;

	void PlayerID(std::uint32_t playerID);
	std::uint32_t PlayerID() const;
private:
	std::map<Actions::Move, int> mMoveActionMap;
	std::map<Actions::User, int> mUserActionMap;
	std::map<Actions::Global, int> mGlobalActionMap;

	std::map<int, bool> mKeys;
	std::map<int, bool> mKeysLast;

	std::map<int, bool> mButtons;
	std::map<int, bool> mButtonsLast;

	std::pair<double, double> mMousePos;
	std::pair<double, double> mMouseLastPos;

	Graphics* mContext;

	float mDeltaTime;
	float mLastFrame;

	std::uint32_t mPlayerID;
};

