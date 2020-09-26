#include "Systems/sys_Physics.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace System
{
    void sys_Physics::Init()
    {
    }

    void sys_Physics::Update()
    {
        for (const auto& entityA : mEntities)
        {
            auto& eColliderA = gCoordinator.GetComponent<Component::com_Collider>(entityA);
            auto& eTransformA = gCoordinator.GetComponent<Component::com_Transform>(entityA);

            for (const auto& entityB : mEntities)
            {
                if (entityA == entityB) {
                    continue;
                }

                auto& eColliderB = gCoordinator.GetComponent<Component::com_Collider>(entityB);
                auto& eTransformB = gCoordinator.GetComponent<Component::com_Transform>(entityB);

                eColliderA.TestCollision(&eTransformA, &eColliderB, &eTransformB);
            }
        }
    }
}