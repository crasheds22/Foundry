#ifndef __PROTO_COLLIDER_H__
#define __PROTO_COLLIDER_H__

#include "IPrototype.h"

namespace Prototype
{
	/** @class Collider
	 *
	 *	@brief Details how to spawn an invisible collider in the world
	 *
	 *	@author Aaron Thomson*/
	class Collider
		: public IPrototype
	{
	public:
		/** @brief Constructor
		 */
		Collider(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax, int type);

		/** @brief Destructor
		 */
		~Collider();

	private:

	};
}

#endif
