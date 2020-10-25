#ifndef __PROTO_TABLE_H__
#define __PROTO_TABLE_H__

#include "IPrototype.h"

namespace Prototype
{
	class Table
		: public IPrototype
	{
	public:
		Table(std::string name, Component::com_Transform transform);

		~Table();

	private:
	};
}

#endif
