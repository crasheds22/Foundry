#ifndef __PROTO_PLAYER_H__
#define __PROTO_PLAYER_H__

#include "IPrototype.h"
#include "Props.h"

namespace Prototype
{
	class Player
		: public IPrototype
	{
	public:
		Player(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax);

		~Player();

	private:
	};
}

#endif
