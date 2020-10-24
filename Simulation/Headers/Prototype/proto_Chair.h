#ifndef __PROTO_CHAIR_H__
#define __PROTO_CHAIR_H__

#include "IPrototype.h"

namespace Prototype
{
	class Chair
		: public IPrototype
	{
	public:
		Chair(std::string name, Component::com_Transform transform);

	private:
	};
}

#endif
