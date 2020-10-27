#include "Prototype/PrototypeFactory.h"

namespace Prototype
{
	IPrototype* Factory::Make(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax)
	{
		if (name.find("computer") != std::string::npos)
			return new Computer(name, transform, minMax);

		if (name.find("monitor") != std::string::npos)
			return new Monitor(name, transform, minMax);

		//if (name.find("chair") != std::string::npos)
		//	return new Chair(name, transform);

		if (name.find("table") != std::string::npos)
			return new Table(name, transform, minMax);

		//if (name.find("backpack") != std::string::npos)
		//	return new Backpack(name, transform, minMax);

		if (name.find("player") != std::string::npos)
			return new Player(name, transform, minMax);

		//if (name.find("collider") != std::string::npos)
			//return new Collider(name, transform, minMax, 3);

		//if (name.find("floor") != std::string::npos)
			//return new Collider(name, transform, minMax, 2);

		return nullptr;
	}
}
