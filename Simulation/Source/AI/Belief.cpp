#include "AI/Belief.h"

namespace AI 
{
	Belief::Belief()
	{
		mEncountered = std::unordered_map<ECS::Entity, Component::com_Transform&>();
	}

	void Belief::Insert(ECS::Entity entity, Component::com_Transform& pos)
	{
		auto it = mEncountered.find(entity);
		if (it != mEncountered.end())
		{
			it->second = pos;
			return;
		}

		mEncountered.insert(std::pair<ECS::Entity, Component::com_Transform&>(entity, pos));
	}
	
	bool Belief::Find(ECS::Entity entity)
	{
		if (mEncountered.find(entity) != mEncountered.end())
			return true;

		return false;
	}
	
	Component::com_Transform* Belief::Retrieve(ECS::Entity entity)
	{
		auto it = mEncountered.find(entity);

		if (it != mEncountered.end())
			return &it->second;

		return nullptr;
	}
}