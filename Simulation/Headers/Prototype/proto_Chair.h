#ifndef __PROTO_CHAIR_H__
#define __PROTO_CHAIR_H__

#include "IPrototype.h"

namespace Prototype
{
	/** @class Chair
	 *
	 *	@brief Describes what is neeeded for a chair to span in the world
	 *
	 *	@author Aaron Thomson
	 */
	class Chair
		: public IPrototype
	{
	public:
		/** @brief Constructor
		 */
		Chair(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax);

		/** @brief Destructor
		 */
		~Chair();

	private:
	};
}

#endif
