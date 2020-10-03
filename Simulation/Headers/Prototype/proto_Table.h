#ifndef __PROTO_TABLE_H__
#define __PROTO_TABLE_H__

#include <string>

#include "ECS/Types.h"

#include "Components/com_Transform.h"

namespace Prototype
{
	class Table
	{
	public:
		Table(std::string name, Component::com_Transform);

		ECS::Entity ID() const;
		std::string Name() const;

	private:
		ECS::Entity mID;
		std::string mName;

	};
}

#endif
