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
        //for (const auto& entityA : mEntities)
        //{
        //    auto& eColliderA = gCoordinator.GetComponent<Component::com_Collider>(entityA);
        //    auto& eTransformA = gCoordinator.GetComponent<Component::com_Transform>(entityA);
        //
        //    for (const auto& entityB : mEntities)
        //    {
        //        if (entityA == entityB) {
        //            continue;
        //        }
        //
        //        auto& eColliderB = gCoordinator.GetComponent<Component::com_Collider>(entityB);
        //        auto& eTransformB = gCoordinator.GetComponent<Component::com_Transform>(entityB);
        //
        //        CollisionPoint temp = eColliderA.TestCollision(&eTransformA, &eColliderB, &eTransformB);
        //        if (temp.HasCollision()) 
        //        {
        //            Collision temp2(entityA, entityB, temp);
        //            CollisionList.push_back(temp2);
        //        }
        //    }
        //}
        //
        //for (Collision collide : CollisionList)
        //{
        //    auto& pA = gCoordinator.GetComponent<Component::com_Physics>(collide.EntityA());
        //    auto& pB = gCoordinator.GetComponent<Component::com_Physics>(collide.EntityB());
        //
        //    auto& tA = gCoordinator.GetComponent<Component::com_Transform>(collide.EntityA());
        //    auto& tB = gCoordinator.GetComponent<Component::com_Transform>(collide.EntityB());
        //
        //    float restitution = Physics::CalculateRestitution(pA.Restitution(), pB.Restitution());
        //    float radiusA = Physics::CalculateRadius(collide.Point().PointA(), collide.Point().PointB(), pA.CentreOfMass(), tA.Position());
        //    float radiusB = Physics::CalculateRadius(collide.Point().PointB(), collide.Point().PointA(), pB.CentreOfMass(), tB.Position());
        //    float velocityDifference = Physics::CalculateVelocityDifference(collide.Point().Normal(), pA.Velocity(), pB.Velocity());
        //    float angleAroundA = Physics::CalculateAngleAround(pA.RotationVel(), radiusA, collide.Point().Normal());
        //    float angleAroundB = Physics::CalculateAngleAround(pB.RotationVel(), radiusB, collide.Point().Normal());
        //    float beastA = Physics::CalculateBeast(radiusA, collide.Point().Normal(), pA.InertiaTensor());
        //    float beastB = Physics::CalculateBeast(radiusB, collide.Point().Normal(), pB.InertiaTensor());
        //
        //    float lambda = (restitution * (velocityDifference + angleAroundA - angleAroundB)) / (pA.InvMass() + pB.InvMass() + (beastA + beastB));
        //}
        //
        //for (const auto& entityA : mEntities)
        //{
        //    //Apply Force
        //}
    }
}