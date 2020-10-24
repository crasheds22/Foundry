#ifndef __PROTOTYPE_FACTORY_H__
#define __PROTOTYPE_FACTORY_H__

#include "IPrototype.h"
#include "Prototypes.h"

namespace Prototype
{
	class Factory
	{
	public:
		static IPrototype* Make(std::string name);
	};
}

#endif
