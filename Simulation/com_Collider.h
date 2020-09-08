#pragma once

/**
* @class Collider
* 
* @brief
* @author Kristian
*/

namespace Component
{
	enum class ColliderType {
		BOX,
		SPHERE,
		UNDEFINED
	};

	class Collider
	{
	public:
		/**
		* @brief constructor
		*/
		Collider();

		/**
		* @brief destructor
		*/
		virtual ~Collider();

		/**
		* @brief set type
		* 
		* @param CollideType type - enum class for type of collider
		*/
		void Type(ColliderType type);

		/**
		* @brief get type
		* 
		* @return ColliderType mType - enum class for type of collider
		*/
		ColliderType Type();
	private:
		ColliderType mType; /// enum class for type of collider (i.e. box, sphere, etc.)
	};
}