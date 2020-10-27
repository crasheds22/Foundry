#include "Prototype/PrototypeFactory.h"

namespace Prototype
{
	IPrototype* Factory::Make(std::string name, Component::com_Transform transform)
	{
		if (name.find("computer") != std::string::npos)
			return new Computer(name, transform);

		if (name.find("monitor") != std::string::npos)
			return new Monitor(name, transform);

		//if (name.find("chair") != std::string::npos)
		//	return new Chair(name, transform);

		if (name.find("table") != std::string::npos)
			return new Table(name, transform);

		if (name.find("backpack") != std::string::npos)
			return new Backpack(name, transform);

		if (name.find("player") != std::string::npos)
			return new Player(name, transform);

		return nullptr;
	}
}
