#pragma once

namespace Actions
{
	/** @enum Global
	 *
	 *	@brief Actions that can be taken on a global scale
	 */
	enum class Global
	{
		QUIT
		,PAUSE
		,MENU
		,RESUME
	};

	/** @enum Move
	 *
	 *	@brief Actions relate to motion
	 */
	enum class Move
	{
		LEFT
		,RIGHT
		,FORWARD
		,BACKWARD
		,UP
		,DOWN
	};

	/** @enum User
	 *
	 *	@brief Actions related to the user
	 */
	enum class User
	{
		USE
	};
}
