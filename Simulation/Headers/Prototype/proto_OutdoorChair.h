#ifndef __PROTO_OUTDOORCHAIR_H__
#define __PROTO_OUTDOORCHAIR_H__

#include <string>

#include "ECS/Types.h"

#include "Components/com_Transform.h"

namespace Prototype
{
	class OutdoorChair
	{
	public:
		OutdoorChair(std::string name, Component::com_Transform trandsform);

		ECS::Entity ID() const;
		std::string Name() const;

	private:
		ECS::Entity mID;
		std::string mName;
	};
}

#endif
