#ifndef __PROTO_BUSH_H__
#define __PROTO_BUSH_H__

#include "IPrototype.h"

namespace Prototype
{
	class Bush
		: public IPrototype
	{
	public:
		Bush(std::string name, Component::com_Transform transform);

	private:
	};
}

#endif
