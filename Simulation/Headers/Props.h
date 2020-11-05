#pragma once

#include <map>
#include <utility>

#include "Actions.h"
#include "Graphics/Graphics.h"
#include "Singleton.h"

/** @class Props
 *
 *	@brief auxilliary class for purposes the help the course of the game
 *
 *	@author Aaron Thomson
 */
class Props
	: public Singleton<Props>
{
public:
	/** @brief Constructor
	 */
	Props();

	/** @brief tells openGL to update the state of all the keys
	 */
	void UpdateKeys();
	
	/** @brief Updates the state of the mouse
	 */
	void UpdateMouse();
	
	/** @brief Updates delta time
	 */
	void UpdateDT();

	/** @brief Returns if the action key requested has been pressed
	 */
	bool Pressed(Actions::Move action);
	
	/** @brief Returns if the action key requested has been pressed
	 */
	bool Pressed(Actions::User action);
	
	/** @brief Returns if the action key requested has been pressed
	 */
	bool Pressed(Actions::Global action);

	/** @brief Returns if the action key requested has been released
	 */
	bool Released(Actions::Move action);
	
	/** @brief Returns if the action key requested has been released
	 */
	bool Released(Actions::User action);
	
	/** @brief Returns if the action key requested has been released
	 */
	bool Released(Actions::Global action);

	/** @brief Retursn if the key was just released 
	 */
	bool JustReleased(Actions::Move action);
	
	/** @brief Retursn if the key was just released
	 */
	bool JustReleased(Actions::User action);
	
	/** @brief Retursn if the key was just released
	 */
	bool JustReleased(Actions::Global action);

	/** @brief Returns the difference in mouse screen locations 
	 */
	std::pair<double, double> MouseOffset();
	
	/** @brief Returns the mouse location this frame 
	 */
	std::pair<double, double> ThisMouse();
	
	/** @brief Returns the mouse location last frame
	 */
	std::pair<double, double> LastMouse();

	/** @brief Returns the difference in time between this and the last frame
	 */
	float DeltaTime() const;

	/** @brief Assigns the player ID
	 */
	void PlayerID(std::uint32_t playerID);
	
	/** @brief Returns the player ID
	 */
	std::uint32_t PlayerID() const;
private:
	std::map<Actions::Move, int> mMoveActionMap;	/*!< Map from movement action to keys */
	std::map<Actions::User, int> mUserActionMap;	/*!< Map from user action to keys */
	std::map<Actions::Global, int> mGlobalActionMap;/*!< Map from global actions to keys */

	std::map<int, bool> mKeys;		/*!< Map from keys to state */
	std::map<int, bool> mKeysLast;	/*!< Map of keys to their state in theprevious frame */

	std::map<int, bool> mButtons;	/*!< Map of mouse buttons to their state */
	std::map<int, bool> mButtonsLast;	/*!< Map of mouse buttons to their state in the last frame */

	std::pair<double, double> mMousePos;	/*!< Mouse position this frame */
	std::pair<double, double> mMouseLastPos;/*!< Mouse position last frame */

	Graphics* mContext;	/*!< Pointer to the active context */

	float mDeltaTime;	/*!< Change in time from the current to the previous frame */
	float mLastFrame;	/*!< Time at the last frame */

	std::uint32_t mPlayerID;	/*!< The player ID */
};

