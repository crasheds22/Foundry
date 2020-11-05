#ifndef __PROTO_MONITOR_H__
#define __PROTO_MONITOR_H__

#include "IPrototype.h"

namespace Prototype
{
	/** @class Monitor
	 *
	 *	@brief Details the resources needed for a basic monitor to spwan in the world
	 *
	 *	@author Aaron Thomson
	 */
	class Monitor
		: public IPrototype
	{
	public:
		/** @brief Constructor
		 */
		Monitor(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax);

		/** @brief Destrcutor
		 */
		~Monitor();

	private:
	};
}

#endif
