#ifndef __PROTO_BACKPACK_H__
#define __PROTO_BACKPACK_H__

#include "IPrototype.h"

namespace Prototype
{
	/** @class Backpack
	 *
	 *	@brief Defines what is needed to spawn a backpack in the world
	 *
	 *	@author Aaron Thomson
	 */
	class Backpack
		: public IPrototype
	{
	public:
		/** @brief Constructor
		 */
		Backpack(std::string name, Component::com_Transform transform);

		/** @brief Destructor 
		 */
		~Backpack();

	private:
	};
}

#endif
