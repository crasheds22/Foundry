#ifndef __PROTO_TOM_H__
#define __PROTO_TOM_H__

#include "IPrototype.h"

namespace Prototype
{
	class Tom
		: public IPrototype
	{
	public:
		Tom(std::string name, Component::com_Transform transform);

	private:
	};
}

#endif
