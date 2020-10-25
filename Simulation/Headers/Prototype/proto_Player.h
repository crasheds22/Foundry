#ifndef __PROTO_PLAYER_H__
#define __PROTO_PLAYER_H__

#include "IPrototype.h"

namespace Prototype
{
	class Player
		: public IPrototype
	{
	public:
		Player(std::string name, Component::com_Transform transform);

		~Player();

	private:
	};
}

#endif
