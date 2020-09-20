#pragma once

#include <map>
#include <utility>

#include "Actions.h"
#include "Graphics/Graphics.h"

class Props
{
public:
	static Props& Instance();

	Props(const Props& p) = delete;
	void operator=(const Props& p) = delete;

	void SetContext(Graphics* context);

	void UpdateKeys();
	void UpdateMouse();

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


private:
	Props();

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
};

