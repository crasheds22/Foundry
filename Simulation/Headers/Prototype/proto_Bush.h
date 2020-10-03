#ifndef __PROTO_BUSH_H__
#define __PROTO_BUSH_H__

#include "ECS/Types.h"

#include "Components/com_Transform.h"

#include <string>

namespace Prototype
{
	class Bush
	{
	public:
		Bush(std::string name, Component::com_Transform transform);

		ECS::Entity ID() const;
		std::string Name() const;

	private:
		ECS::Entity mID;
		std::string mName;
	};
}

#endif
