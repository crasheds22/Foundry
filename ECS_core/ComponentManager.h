#pragma once

#include "ComponentArray.h"
#include "Types.h"

#include <any>
#include <memory>
#include <unordered_map>

namespace ECS
{
	class ComponentManager
	{
	public:
		template<typename Component>
		void RegisterComponent()
		{
			const char* typeName = typeid(Component).name();

			assert(mComponentTypes.find(typeName) == mComponentTypes.end()
				&& "Registering component more than once.");

			mComponentTypes.insert({ typeName, mNextComponentType });
			mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<Component>>() });

			++mNextComponentType;
		}

		template<typename Component>
		ComponentType GetComponentType()
		{
			const char* typeName = typeid(Component).name();

			assert(mComponentTypes.find(typeName) != mComponentTypes.end()
				&& "Component not registered before use.");

			return mComponentTypes[typeName];
		}

		template<typename Component>
		void AddComponent(Entity entity, Component component)
		{
			GetComponentArray<Component>()->InsertData(entity, component);
		}

		template<typename Component>
		void RemoveComponent(Entity entity)
		{
			GetComponentArray<Component>()->RemoveData(entity);
		}

		template<typename Component>
		Component& GetComponent(Entity entity)
		{
			return GetComponentArray<Component>()->GetData(entity);
		}

		void EntityDestroyed(Entity entity)
		{
			for (auto const& pair : mComponentArrays)
			{
				auto const& component = pair.second;

				component->EntityDestroyed(entity);
			}
		}

	private:
		std::unordered_map<const char*, ComponentType> mComponentTypes;
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays;
		ComponentType mNextComponentType;

		template <typename Component>
		std::shared_ptr<ComponentArray<Component>> GetComponentArray()
		{
			const char* typeName = typeid(Component).name();

			assert(mComponentTypes.find(typeName) != mComponentTypes.end()
				&& "Component not registered before use.");

			return std::static_pointer_cast<ComponentArray<Component>>(mComponentArrays[typeName]);
		}
	};
}
