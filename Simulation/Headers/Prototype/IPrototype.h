#ifndef __IPROTOTYPE_H__
#define __IPROTOTYPE_H__

#include <string>
#include "ECS/Types.h"
#include "Components/com_Transform.h"

namespace Prototype
{
	class IPrototype
	{
	public:
		IPrototype(std::string name) {}

		virtual ~IPrototype() = 0;

		ECS::Entity ID() const { return mID; }
		std::string Name() const { return mName; }

	private:
		ECS::Entity mID = 0;
		std::string mName = "";
	};
}

#endif
