#pragma once

namespace Component
{
	class com_Player
	{
	public:
		com_Player() : mMoveSpeed(0.0f), mRotateSpeed(0.0f) {};
		com_Player(float move, float rotate);

		float MoveSpeed() const;
		float RotateSpeed() const;

	private:
		float mMoveSpeed;
		float mRotateSpeed;

	};
}
