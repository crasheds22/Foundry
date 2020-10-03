#ifndef __PROTO_APPLE_H__
#define __PROTO_APPLE_H__

#include "IPrototype.h"

namespace Prototype
{
	class Apple
		: public IPrototype
	{
	public:
		Apple(std::string name, Component::com_Transform transform);

	private:

	};
}

#endif
