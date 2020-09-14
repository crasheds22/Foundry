#include "Components/com_Player.h"

namespace Component
{
	com_Player::com_Player(float move, float rotate) 
		: mMoveSpeed(move), mRotateSpeed(rotate)
	{
	}

	float com_Player::MoveSpeed() const
	{
		return mMoveSpeed;
	}

	float com_Player::RotateSpeed() const
	{
		return mRotateSpeed;
	}
}
