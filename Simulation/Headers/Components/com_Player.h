#pragma once

namespace Component
{
	/** @class com_Player
	 *
	 *	@brief A component for a player controlled entity
	 *	
	 *	@author Aaron Thomson
	 */
	class com_Player
	{
	public:
		/** @brief Constructor
		 */
		com_Player() : mMoveSpeed(0.0f), mRotateSpeed(0.0f) {};
		
		/** @brief Constructor
		 *
		 *	@param move Initial move speed
		 *	@param rotate Initial rotation speed
		 */
		com_Player(float move, float rotate);

		/** @brief Returns the movement speed
		 */
		float MoveSpeed() const;
		
		/** @brief Returns the rotation speed
		 */
		float RotateSpeed() const;

	private:
		float mMoveSpeed;	/*<! The players movement speed */
		float mRotateSpeed;	/*<! The players rotation speed */

	};
}
