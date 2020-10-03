#ifndef __PROTO_ROTTENAPPLE_H_
#define __PROTO_ROTTENAPPLE_H__

#include "IPrototype.h"

namespace Prototype
{
	class RottenApple
		: public IPrototype
	{
	public:
		RottenApple(std::string name, Component::com_Transform transform);

	private:

	};
}

#endif
