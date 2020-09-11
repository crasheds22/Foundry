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
		template<typename TComponent>
		void RegisterComponent()
		{
			mComponentManager->RegisterComponent<TComponent>();
		}

		template<typename TComponent>
		void AddComponent(Entity entity, TComponent component)
		{
			mComponentManager->AddComponent<TComponent>(entity, component);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<TComponent>(), true);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename TComponent>
		void RemoveComponent(Entity entity)
		{
			mComponentManager->RemoveComponent<TComponent>(entity);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<TComponent>(), false);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename TComponent>
		TComponent& GetComponent(Entity entity)
		{
			return mComponentManager->GetComponent<TComponent>(entity);
		}

		template<typename TComponent>
		ComponentType GetComponentType()
		{
			return mComponentManager->GetComponentType<TComponent>();
		}

		//System methods
		template<typename TSystem>
		std::shared_ptr<TSystem> RegisterSystem()
		{
			return mSystemManager->RegisterSystem<TSystem>();
		}

		template<typename TSystem>
		void SetSystemSignature(Signature signature)
		{
			mSystemManager->SetSignature<TSystem>(signature);
		}

	private:
		std::unique_ptr<ComponentManager>	mComponentManager;
		std::unique_ptr<EntityManager>		mEntityManager;
		std::unique_ptr<SystemManager>		mSystemManager;
	};
}
