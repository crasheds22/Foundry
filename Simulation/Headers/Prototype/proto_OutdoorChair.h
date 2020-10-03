#ifndef __PROTO_OUTDOORCHAIR_H__
#define __PROTO_OUTDOORCHAIR_H__

#include "IPrototype.h"

namespace Prototype
{
	class OutdoorChair
		: public IPrototype
	{
	public:
		OutdoorChair(std::string name, Component::com_Transform transform);

	private:

	};
}

#endif
