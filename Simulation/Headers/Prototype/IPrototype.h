#ifndef __IPROTOTYPE_H__
#define __IPROTOTYPE_H__

#include <string>
#include "ECS/Types.h"
#include "Components/Components.h"
#include <utility>

namespace Prototype
{
	class IPrototype
	{
	public:
		IPrototype(std::string name) : mName(name) {}

		virtual ~IPrototype() = 0 { };

		ECS::Entity ID() const { return mID; }
		std::string Name() const { return mName; }

	protected:
		ECS::Entity mID = 0;

	private:
		std::string mName = "";
	};
}

#endif
