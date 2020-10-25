#ifndef __PROTO_BACKPACK_H__
#define __PROTO_BACKPACK_H__

#include "IPrototype.h"

namespace Prototype
{
	class Backpack
		: public IPrototype
	{
	public:
		Backpack(std::string name, Component::com_Transform transform);

		~Backpack();

	private:
	};
}

#endif
