#ifndef __PROTO_WORLD_H__
#define __PROTO_WORLD_H__

#include "IPrototype.h"

namespace Prototype
{
	/** @class World
	 *
	 *	@brief Defines the resources needed to create a world
	 *
	 *	@author Aaron Thomson
	 */
	class World
		: public IPrototype
	{
	public:
		/** @brief Constructor
		 */
		World(std::string name);

		/** @brief Destructor
		 */
		~World();

	private:

	};
}

#endif
