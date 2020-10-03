#ifndef __PROTO_DESK_H__
#define __PROTO_DESK_H__

#include <string>

#include "ECS/Types.h"

#include "Components/com_Transform.h"

namespace Prototype
{
	class Desk
	{
	public:
		Desk(std::string name, Component::com_Transform transform);

		ECS::Entity ID() const;
		std::string Name() const;

	private:
		ECS::Entity mID;
		std::string mName;

	};
}

#endif
