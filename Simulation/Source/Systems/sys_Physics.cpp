#include "Systems/sys_Physics.h"

#include "ECS/Coordinator.h"
extern ECS::Coordinator gCoordinator;

namespace System
{
    void sys_Physics::Init()
    {
        ref = &Props::Instance();
    }
    
    void sys_Physics::Update()
    {
        for (const auto& entityA : mEntities)
        {
            auto& ePhysicsA = gCoordinator.GetComponent<Component::com_Physics>(entityA);
            auto& eTransformA = gCoordinator.GetComponent<Component::com_Transform>(entityA);
        
            for (const auto& entityB : mEntities)
            {
                if (entityA == entityB) {
                    continue;
                }
        
                auto& ePhysicsB = gCoordinator.GetComponent<Component::com_Physics>(entityB);
                auto& eTransformB = gCoordinator.GetComponent<Component::com_Transform>(entityB);
        
                CollisionPoint temp = ePhysicsA.Collidercom()->TestCollision(&eTransformA, ePhysicsB.Collidercom(), &eTransformB);
                if (temp.HasCollision()) 
                {
                    Collision temp2(entityA, entityB, temp);
                    CollisionList.push_back(temp2);
                }
            }
        }
        
        for (Collision collide : CollisionList)
        {
            auto& pA = gCoordinator.GetComponent<Component::com_Physics>(collide.EntityA());
            auto& pB = gCoordinator.GetComponent<Component::com_Physics>(collide.EntityB());
        
            auto& tA = gCoordinator.GetComponent<Component::com_Transform>(collide.EntityA());
            auto& tB = gCoordinator.GetComponent<Component::com_Transform>(collide.EntityB());
        
            float restitution = Physics::CalculateRestitution(pA.Restitution(), pB.Restitution());
            float radiusA = Physics::CalculateRadius(collide.Point().PointA(), collide.Point().PointB(), pA.CentreOfMass(), tA.Position());
            float radiusB = Physics::CalculateRadius(collide.Point().PointB(), collide.Point().PointA(), pB.CentreOfMass(), tB.Position());
            float velocityDifference = Physics::CalculateVelocityDifference(collide.Point().Normal(), pA.Velocity(), pB.Velocity());
            float angleAroundA = Physics::CalculateAngleAround(pA.RotationVel(), radiusA, collide.Point().Normal());
            float angleAroundB = Physics::CalculateAngleAround(pB.RotationVel(), radiusB, collide.Point().Normal());
            float beastA = Physics::CalculateBeast(radiusA, collide.Point().Normal(), pA.Collidercom()->Inertia());
            float beastB = Physics::CalculateBeast(radiusB, collide.Point().Normal(), pB.Collidercom()->Inertia());
        
            float lambda = (restitution * (velocityDifference + angleAroundA - angleAroundB)) / (pA.InvMass() + pB.InvMass() + (beastA + beastB));

            pA.Velocity(Physics::CalculateCollisionVel(pA.Velocity(), lambda, pA.Mass(), collide.Point().Normal()));
            pB.Velocity(Physics::CalculateCollisionVel(pB.Velocity(), -lambda, pB.Mass(), collide.Point().Normal()));

            pA.RotationVel(Physics::CalculateCollisionRotVel(pA.RotationVel(), lambda, pA.Collidercom()->Inertia(), radiusA, collide.Point().Normal()));
            pB.RotationVel(Physics::CalculateCollisionRotVel(pB.RotationVel(), -lambda, pB.Collidercom()->Inertia(), radiusB, collide.Point().Normal()));
        }
        
        for (const auto& entity : mEntities)
        {
            auto& ePhysics = gCoordinator.GetComponent<Component::com_Physics>(entity);
            auto& eTransform = gCoordinator.GetComponent<Component::com_Transform>(entity);

            eTransform.Position(eTransform.Position() + ePhysics.Velocity() * ref->DeltaTime());
            //eTransform.Position(eTransform.Position() + glm::vec3(0, -0.1, 0) * ref->DeltaTime());

            eTransform.Rotation(eTransform.Rotation() + ePhysics.RotationVel() * ref->DeltaTime());
        }
    }
    
}