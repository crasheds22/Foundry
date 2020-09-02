#pragma once

#include "Types.h"

#include <array>
#include <cassert>
#include <unordered_map>

namespace ECS
{
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	};

	template<typename Component>
	class ComponentArray : public IComponentArray
	{
	public:
		void InsertData(Entity entity, Component component)
		{
			assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end()
				&& "Component added to same entity more than once."); //<------ Send this via a log to screen/file

			//Put new entry at end
			size_t newIndex = mSize;

			mEntityToIndexMap[entity] = newIndex;
			mIndexToEntityMap[newIndex] = entity;

			mComponentArray[newIndex] = component;

			++mSize;
		}

		void RemoveData(Entity entity)
		{
			assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()
				&& "removing non-existant component.");

			//Copy element at end into deleted elements place to maintain density
			size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
			size_t indexOfLastElement = mSize - 1;

			mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

			//Update map t point to moved spot
			Entity entityofLastElement = mIndexToEntityMap[indexOfLastElement];
			mEntityToIndexMap[entityofLastElement] = indexOfRemovedEntity;
			mIndexToEntityMap[indexOfRemovedEntity] = entityofLastElement;

			mEntityToIndexMap.erase(entity);
			mIndexToEntityMap.erase(indexOfLastElement);

			--mSize;
		}

		Component& GetData(Entity entity)
		{
			assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()
				&& "Retrieving non-existant component.");

			return mComponentArray[mEntityToIndexMap[entity]];
		}

		void EntityDestroyed(Entity entity) override
		{
			if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
			{
				RemoveData(entity);
			}
		}


	private:
		std::array<Component, MAX_ENTITIES> mComponentArray;

		std::unordered_map<Entity, size_t> mEntityToIndexMap;
		std::unordered_map<size_t, Entity> mIndexToEntityMap;

		size_t mSize;
	};
}
