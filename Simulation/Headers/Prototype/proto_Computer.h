#ifndef __PROTO_COMPUTER_H__
#define __PROTO_COMPUTER_H__

#include "IPrototype.h"

namespace Prototype
{
	class Computer
		: public IPrototype
	{
	public:
		Computer(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax);

		~Computer();

	private:
	};
}

#endif
