#ifndef __PROTO_PLAYER_H__
#define __PROTO_PLAYER_H__

#include "IPrototype.h"
#include "Props.h"

namespace Prototype
{
	/** @class Player
	 *
	 *	@brief Details the resources needed for a player entity to spawn
	 *
	 *	@author Aaron Thomson
	 */
	class Player
		: public IPrototype
	{
	public:
		/** @brief Constructor
		 */
		Player(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax);

		/** @brief Destructor
		 */
		~Player();

	private:
	};
}

#endif
