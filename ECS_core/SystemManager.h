#pragma once

#include "System.h"
#include "Types.h"

#include <cassert>
#include <memory>
#include <unordered_map>

namespace ECS
{
	class SystemManager
	{
	public:
		template<typename System>
		std::shared_ptr<ECS::System> RegisterSystem()
		{
			const char* typeName = typeid(System).name();

			assert(mSystems.find(typeName) == mSystems.end()
				&& "Registering system more than once.");

			auto system = std::make_shared<ECS::System>();
			mSystems.insert({ typeName, system });

			return system;
		}

		template<typename System>
		void SetSignature(Signature signature)
		{
			const char* typeName = typeid(System).name();

			assert(mSystems.find(typeName) != mSystems.end()
				&& "System used before registered.");

			mSignatures.insert({ typeName, signature });
		}

		void EntityDestroyed(Entity entity)
		{
			for (auto const& pair : mSystems)
			{
				auto const& system = pair.second;

				system->mEntities.erase(entity);
			}
		}

		void EntitySignatureChanged(Entity entity, Signature entitySignature)
		{
			for (auto const& pair : mSystems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = mSignatures[type];

				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->mEntities.insert(entity);
				}
				else
				{
					system->mEntities.erase(entity);
				}
			}
		}

	private:
		std::unordered_map<const char*, Signature> mSignatures;
		std::unordered_map<const char*, std::shared_ptr<ECS::System>> mSystems;
	};
}
