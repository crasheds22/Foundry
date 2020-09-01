#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "Types.h"

#include <memory>

namespace ECS
{
	class Coordinator
	{
	public:
		void Init()
		{
			mComponentManager = std::make_unique<ComponentManager>();
			mEntityManager = std::make_unique<EntityManager>();
			mSystemManager = std::make_unique<SystemManager>();
		}

		//Entity methods
		Entity CreateEntity()
		{
			return mEntityManager->CreateEntity();
		}

		void DestroyEntity(Entity entity)
		{
			mEntityManager->DestroyEntity(entity);

			mComponentManager->EntityDestroyed(entity);

			mSystemManager->EntityDestroyed(entity);
		}

		//Component methods
		template<typename Component>
		void RegisterComponent()
		{
			mComponentManager->RegisterComponent<Component>();
		}

		template<typename Component>
		void AddComponent(Entity entity, Component component)
		{
			mComponentManager->AddComponent<Component>(entity, component);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<Component>(), true);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename Component>
		void RemoveComponent(Entity entity)
		{
			mComponentManager->RemoveComponent<Component>(entity);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<Component>(), false);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename Component>
		Component& GetComponent(Entity entity)
		{
			return mComponentManager->GetComponent<Component>(entity);
		}

		template<typename Component>
		ComponentType GetComponentType()
		{
			return mComponentManager->GetComponentType<Component>();
		}

		template<typename Component>
		std::shared_ptr<ComponentArray<Component>> GetComponentArray()
		{
			return mComponentManager->GetComponentArray<Component>();
		}

		//System methods
		template<typename System>
		std::shared_ptr<System> RegisterSystem()
		{
			return mSystemManager->RegisterSystem<System>();
		}

		template<typename System>
		void SetSystemSignature(Signature signature)
		{
			mSystemManager->SetSignature<System>(signature);
		}

	private:
		std::unique_ptr<ComponentManager>	mComponentManager;
		std::unique_ptr<EntityManager>		mEntityManager;
		std::unique_ptr<SystemManager>		mSystemManager;
	};
}
