#ifndef __PROTO_TABLE_H__
#define __PROTO_TABLE_H__

#include "IPrototype.h"

namespace Prototype
{
	/** @class Table
	 *
	 *	@brief Details the resources needed for spawning a table
	 *
	 *	@author Aaron Thomson
	 */
	class Table
		: public IPrototype
	{
	public:
		/** @brief Constructor
		 */
		Table(std::string name, Component::com_Transform transform, std::pair<glm::vec3, glm::vec3> minMax);

		/** @brief Destructor
		 */
		~Table();

	private:
	};
}

#endif
