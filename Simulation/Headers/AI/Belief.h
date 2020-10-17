#ifndef __BELIEF_H__
#define __BELIEF_H__

#include <unordered_map>

#include "ECS/Types.h"

#include "Components/com_Transform.h"

namespace AI
{
	class Belief
	{
	public:
		Belief();

		void Insert(ECS::Entity entity, Component::com_Transform& pos);
		bool Find(ECS::Entity entity);
		Component::com_Transform& Retrieve(ECS::Entity entity);

	private:
		std::unordered_map<ECS::Entity, Component::com_Transform&> mEncountered;
	};
}

#endif
