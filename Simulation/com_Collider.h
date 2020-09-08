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
		* @brief constructs collider from type
		* 
		* @param ColliderType type - type of collider
		*/
		Collider(ColliderType type);

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
	protected:
		ColliderType mType; /// enum class for type of collider (i.e. box, sphere, etc.)
	};
}