#ifndef __PROTO_MONITOR_H__
#define __PROTO_MONITOR_H__

#include "IPrototype.h"

namespace Prototype
{
	class Monitor
		: public IPrototype
	{
	public:
		Monitor(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax);

		~Monitor();

	private:
	};
}

#endif
