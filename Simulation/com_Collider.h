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
		Collider();

		virtual ~Collider();

		void Type(ColliderType type);
		ColliderType Type();
	private:
		ColliderType mType;
	};
}