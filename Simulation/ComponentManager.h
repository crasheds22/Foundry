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
		template<typename TComponent>
		void RegisterComponent()
		{
			const char* typeName = typeid(TComponent).name();

			assert(mComponentTypes.find(typeName) == mComponentTypes.end()
				&& "Registering component more than once.");

			mComponentTypes.insert({ typeName, mNextComponentType });
			mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<TComponent>>() });

			++mNextComponentType;
		}

		template<typename TComponent>
		ComponentType GetComponentType()
		{
			const char* typeName = typeid(TComponent).name();

			assert(mComponentTypes.find(typeName) != mComponentTypes.end()
				&& "Component not registered before use.");

			return mComponentTypes[typeName];
		}

		template<typename TComponent>
		void AddComponent(Entity entity, TComponent component)
		{
			GetComponentArray<TComponent>()->InsertData(entity, component);
		}

		template<typename TComponent>
		void RemoveComponent(Entity entity)
		{
			GetComponentArray<TComponent>()->RemoveData(entity);
		}

		template<typename TComponent>
		TComponent& GetComponent(Entity entity)
		{
			return GetComponentArray<TComponent>()->GetData(entity);
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
		std::unordered_map<const char*, ComponentType> mComponentTypes{};
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};
		ComponentType mNextComponentType{};

		template <typename TComponent>
		std::shared_ptr<ComponentArray<TComponent>> GetComponentArray()
		{
			const char* typeName = typeid(TComponent).name();

			assert(mComponentTypes.find(typeName) != mComponentTypes.end()
				&& "Component not registered before use.");

			return std::static_pointer_cast<ComponentArray<TComponent>>(mComponentArrays[typeName]);
		}
	};
}
