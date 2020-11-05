#ifndef __PROTOTYPE_FACTORY_H__
#define __PROTOTYPE_FACTORY_H__

#include "IPrototype.h"
#include "Prototypes.h"

#include "Components/com_Transform.h"

namespace Prototype
{
	/** @class Factory
	 *
	 *	@brief Used to make prototypes for the world
	 *
	 *	@author Aaron Thomson
	 */
	class Factory
	{
	public:
		/** @brief Makes a true entity from a prototype with the values passed in
		 */
		static IPrototype* Make(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax);
	};
}

#endif
