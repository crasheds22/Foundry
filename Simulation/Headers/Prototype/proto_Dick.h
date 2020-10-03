#ifndef __PROTO_DICK_H__
#define __PROTO_DICK_H__

#include "IPrototype.h"

namespace Prototype
{
	class Dick
		: public IPrototype
	{
	public:
		Dick(std::string name, Component::com_Transform transform);

	private:

	};
}

#endif
