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
        bool duplicate = false;

        for (const auto& entityA : mEntities)
        {
            auto& ePhysicsA = gCoordinator.GetComponent<Component::com_Physics>(entityA);
            auto& eTransformA = gCoordinator.GetComponent<Component::com_Transform>(entityA);
        
            for (const auto& entityB : mEntities)
            {
                duplicate = false;

                if (entityA == entityB) {
                    continue;
                }
        
                auto& ePhysicsB = gCoordinator.GetComponent<Component::com_Physics>(entityB);

                if (ePhysicsA.Dynamic() != 0 && ePhysicsB.Dynamic() != 0) {
                    continue;
                }

                auto& eTransformB = gCoordinator.GetComponent<Component::com_Transform>(entityB);
        
                CollisionPoint temp = ePhysicsA.Collidercom()->TestCollision(&eTransformA, ePhysicsB.Collidercom(), &eTransformB);
                if (temp.HasCollision()) 
                {
                    for (Collision collide : CollisionList) 
                    {
                        if (collide.EntityA() == entityB && collide.EntityB() == entityA) {
                            duplicate = true;
                        }
                    }
                    
                    if (!duplicate)
                    {
                        Collision temp2(entityA, entityB, temp);
                        CollisionList.push_back(temp2);
                    }
                }
            }
        }
        
        //Collision resolution step==================================================================================

        for (Collision collide : CollisionList)
        {
            auto& pA = gCoordinator.GetComponent<Component::com_Physics>(collide.EntityA());
            auto& pB = gCoordinator.GetComponent<Component::com_Physics>(collide.EntityB());
        
            auto& tA = gCoordinator.GetComponent<Component::com_Transform>(collide.EntityA());
            auto& tB = gCoordinator.GetComponent<Component::com_Transform>(collide.EntityB());

            glm::vec3 vA;
            glm::vec3 vB;

            //If Static==============================================

            if (pA.Dynamic() != 0)
            {
                vA = glm::vec3(0);
            }

            if (pB.Dynamic() != 0)
            {
                vB = glm::vec3(0);
            }

            //If Player==============================================

            if (collide.EntityA() == ref->PlayerID())
            {
                vA = tA.Front();
                //vA = glm::vec3(0);
            }
            else
            {
                vA = pA.Velocity();
            }

            if (collide.EntityB() == ref->PlayerID())
            {
                vB = tB.Front();
                //vB = glm::vec3(0);
            }
            else
            {
                vB = pB.Velocity();
            }

            //Calculating Lambda==================================================================================

            float restitution = Physics::CalculateRestitution(pA.Restitution(), pB.Restitution());
            glm::vec3 radiusA = Physics::CalculateRadius(collide.Point().PointA(), collide.Point().PointB(), pA.CentreOfMass(), tA.Position());
            glm::vec3 radiusB = Physics::CalculateRadius(collide.Point().PointB(), collide.Point().PointA(), pB.CentreOfMass(), tB.Position());
            float velocityDifference = Physics::CalculateVelocityDifference(collide.Point().Normal(), vA, vB);
            float angleAroundA = Physics::CalculateAngleAround(pA.RotationVel(), radiusA, collide.Point().Normal());
            float angleAroundB = Physics::CalculateAngleAround(pB.RotationVel(), radiusB, collide.Point().Normal());
            float beastA = Physics::CalculateBeast(radiusA, collide.Point().Normal(), pA.Collidercom()->Inertia());
            float beastB = Physics::CalculateBeast(radiusB, collide.Point().Normal(), pB.Collidercom()->Inertia());
        
            float lambda = (restitution * (velocityDifference + angleAroundA - angleAroundB)) / (pA.InvMass() + pB.InvMass() + (beastA + beastB));

            //Resolution step===================================================================================

            if (collide.EntityA() == ref->PlayerID() || collide.EntityB() == ref->PlayerID())
            {
                if (collide.EntityA() == ref->PlayerID() && pB.Dynamic() == 0) // A is player
                {
                    tB.Position(tB.Position() + vA * 1.0f);
                    pB.Velocity(pB.Velocity() + vA * 20.0f);
                }
                else if(collide.EntityB() == ref->PlayerID() && pA.Dynamic() == 0) // B is player
                {
                    tA.Position(tA.Position() + vB * 1.0f);
                    pA.Velocity(pA.Velocity() + vB * 20.0f);
                }
            }
            else
            {
                if (pA.Dynamic() == 0 && pB.Dynamic() == 0) // Both dynamic
                {
                    tA.Position(tA.Position() + collide.Point().Normal() * (collide.Point().Depth() / 2.0f));
                    tB.Position(tB.Position() - collide.Point().Normal() * (collide.Point().Depth() / 2.0f));
                    pA.Velocity(Physics::CalculateCollisionVel(vA, lambda, pA.Mass(), collide.Point().Normal()));
                    pB.Velocity(Physics::CalculateCollisionVel(vB, -lambda, pB.Mass(), collide.Point().Normal()));
                    pA.RotationVel(glm::radians(Physics::CalculateCollisionRotVel(pA.RotationVel(), lambda, pA.Collidercom()->Inertia(), radiusA, collide.Point().Normal())));
                    pB.RotationVel(glm::radians(Physics::CalculateCollisionRotVel(pB.RotationVel(), -lambda, pB.Collidercom()->Inertia(), radiusB, collide.Point().Normal())));
                }
                else if (pA.Dynamic() == 0 && pB.Dynamic() == 2) // B is floor
                {
                    glm::vec3 temp = tA.Position() - collide.Point().Normal() * collide.Point().Depth() / 2.0f;
                    tA.Position(glm::vec3(tA.Position().x, temp.y, tA.Position().z));
                    //pA.Velocity(-Physics::CalculateCollisionVel(vA, lambda, pA.Mass(), collide.Point().Normal()));
                    pA.Velocity((1.0f - pA.Restitution()) * glm::vec3(pA.Velocity().x + pA.RotationVel().x, -pA.Velocity().y * (1.0 - pA.Restitution()), pA.Velocity().z + pA.RotationVel().z));
                    pA.RotationVel(glm::cross(glm::normalize(pA.Velocity()), glm::vec3(0, 1, 0)) * glm::length(pA.Velocity()) / 2.0f);
                }
                else if (pA.Dynamic() == 2 && pB.Dynamic() == 0) // A is floor
                {
                    glm::vec3 temp = tB.Position() + collide.Point().Normal() * collide.Point().Depth() / 2.0f;
                    tB.Position(glm::vec3(tB.Position().x, temp.y, tB.Position().z));
                    //pB.Velocity(-Physics::CalculateCollisionVel(vB, -lambda, pB.Mass(), collide.Point().Normal()));
                    pB.Velocity((1.0f - pB.Restitution()) * glm::vec3(pB.Velocity().x + pB.RotationVel().x, -pB.Velocity().y * (1.0 - pB.Restitution()), pB.Velocity().z + pB.RotationVel().z));
                    pB.RotationVel(glm::cross(glm::normalize(pB.Velocity()), glm::vec3(0, 1, 0)) * glm::length(pB.Velocity()) / 2.0f);
                }
                else if (pA.Dynamic() == 0 && pB.Dynamic() == 3) // B is wall
                {
                    glm::vec3 temp = tA.Position() - collide.Point().Normal() * collide.Point().Depth() / 2.0f;
                    tA.Position(glm::vec3(temp.x, tA.Position().y, temp.z));
                    pA.Velocity(-Physics::CalculateCollisionVel(vA, lambda, pA.Mass(), collide.Point().Normal()));
                }
                else if (pA.Dynamic() == 3 && pB.Dynamic() == 0) // A is wall
                {
                    glm::vec3 temp = tB.Position() + collide.Point().Normal() * collide.Point().Depth() / 2.0f;
                    tB.Position(glm::vec3(temp.x, tB.Position().y, temp.z));
                    pB.Velocity(-Physics::CalculateCollisionVel(vB, -lambda, pB.Mass(), collide.Point().Normal()));
                }
            }

            

        }

        CollisionList.clear();

        //Force application step======================================================================================================
        
        for (const auto& entity : mEntities)
        {
            auto& ePhysics = gCoordinator.GetComponent<Component::com_Physics>(entity);
            auto& eTransform = gCoordinator.GetComponent<Component::com_Transform>(entity);

            if (!(entity == ref->PlayerID()) && ePhysics.Dynamic() == 0 && ref->DeltaTime() < 1.0f) 
            {
                eTransform.Position(eTransform.Position() + ePhysics.Velocity() * ref->DeltaTime());
                eTransform.Rotation(eTransform.Rotation() + ePhysics.RotationVel() * ref->DeltaTime());

                //Gravity=======================================================================================================

                if (ePhysics.Velocity().y > -1.5f && ePhysics.Velocity().y < 1.5f && eTransform.Position().y < -5.5f)
                {
                    glm::vec3 temp = ePhysics.Velocity() -= glm::normalize(ePhysics.Velocity()) * ref->DeltaTime() * 0.3f;
                    ePhysics.Velocity(glm::vec3(temp.x, 0.0f, temp.z));
                    ePhysics.RotationVel(ePhysics.RotationVel() -= glm::normalize(ePhysics.RotationVel()) * ref->DeltaTime() * 0.3f);
                    //eTransform.Position(glm::vec3(eTransform.Position().x, -6.0f, eTransform.Position().z));
                }
                else if (ePhysics.Velocity().y > -20.0f)
                {
                    ePhysics.Velocity(ePhysics.Velocity() + glm::vec3(0, -9.8f, 0) * ref->DeltaTime());
                }
                else
                {
                    ePhysics.Velocity(glm::vec3(ePhysics.Velocity().x, -20.0f, ePhysics.Velocity().y));
                }

                //Linear Decay==================================================================================================

                if (glm::length(ePhysics.Velocity()) > 0.1)
                {
                    glm::vec3 temp = ePhysics.Velocity() -= glm::normalize(ePhysics.Velocity()) * ref->DeltaTime() * 0.3f;
                    ePhysics.Velocity(glm::vec3(temp.x, ePhysics.Velocity().y, temp.z));
                }
                else
                {
                    ePhysics.Velocity(glm::vec3(0));
                }

                //Rotational Decay=======================================================================================================

                if (glm::length(ePhysics.RotationVel()) > 0.1)
                {
                    ePhysics.RotationVel(ePhysics.RotationVel() -= glm::normalize(ePhysics.RotationVel()) * ref->DeltaTime() * 0.1f);
                }
                else
                {
                    ePhysics.RotationVel(glm::vec3(0));
                }
            }
        }
    }
}