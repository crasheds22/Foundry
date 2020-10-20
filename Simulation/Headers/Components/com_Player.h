#pragma once

/**
*	\namespace Component
*
*	The namespace all Components are located in.
*/
namespace Component
{
	/**
	*	\class com_Player
	* 
	*	\brief A class to hold information about the player
	*/
	class com_Player
	{
	public:
		/**
		*	\brief Default constructor
		* 
		*	Defaults mMoveSpeed and mRotateSpeed to 0.0f
		* 
		*	\post Player is constructed with mMoveSpeed and mRotateSpeed equal to 0.0f
		*/
		com_Player() : mMoveSpeed(0.0f), mRotateSpeed(0.0f) {};
		/**
		*	\brief Constructor
		* 
		*	\param [in] move	Movement speed of the player
		*	\param [in] rotate	Rotation speed of the player
		*	\post Player is created with the values passed in
		*/
		com_Player(float move, float rotate);

		/**
		*	\brief mMoveSpeed accessor
		* 
		*	\return mMoveSpeed
		*	\post mMoveSpeed is returned, but unchanged
		*/
		float MoveSpeed() const;
		/**
		*	\brief mRotateSpeed accessor
		* 
		*	\return mRotateSpeed
		*	\post mRotateSpeed is returned, but unchanged
		*/
		float RotateSpeed() const;

	private:
		float mMoveSpeed;	/*!< The movement speed of the player*/
		float mRotateSpeed;	/*!< The rotation speed of the player*/

	};
}
