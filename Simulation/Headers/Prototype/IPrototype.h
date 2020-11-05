#ifndef __IPROTOTYPE_H__
#define __IPROTOTYPE_H__

#include <string>
#include "ECS/Types.h"
#include "Components/Components.h"
#include <utility>

namespace Prototype
{
	/** @class IPrototype
	 *
	 *	@brief Base class for entities in the world, all objects in the world should inherit
	 *
	 *	@author Aaron Thomson
	 */
	class IPrototype
	{
	public:
		/** @brief Constructor
		 */
		IPrototype(std::string name) : mName(name) {}

		/** @brief Destructor
		 */
		virtual ~IPrototype() = 0 { };

		/** @brief Returns the ID of the entity
		 */
		ECS::Entity ID() const { return mID; }
		
		/** @brief Returns the name of the entity
		 */
		std::string Name() const { return mName; }

	protected:
		ECS::Entity mID = 0;	/*!< The ID of the entity */

	private:
		std::string mName = "";	/*!< The name of the entity */
	};
}

#endif
