#ifndef __PROTO_TREE_H__
#define __PROTO_TREE_H__

#include "IPrototype.h"

namespace Prototype
{
	class Tree
		: public IPrototype
	{
	public:
		Tree(std::string name, Component::com_Transform transform);

	private:
	};
}

#endif
