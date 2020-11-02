#pragma once

#include <glm/glm.hpp>

#include "ECS/Types.h"

#include "Components/com_Transform.h"

/** @class Collision Point
 *
 *	@brief Holds information related to the likely point of collision and depth of collision between two bodies
 *
 *	@author Nicholas Subianto
 *	@author Aaron Thomson
 */
class CollisionPoint
{
public:
	/**	@brief Constructor
	 *	
	 *	@param a Point A of collision
	 *	@param b Point B of collision
	 *	@param hasCollided A Flag to indicate a collision has occurred
	 */
	CollisionPoint(glm::vec3 a, glm::vec3 b, bool hasCollided);

	/** @brief Returns Point A
	 */
	glm::vec3 PointA() const;
	
	/** @brief Returns Point B of the collision
	 */
	glm::vec3 PointB() const;
	
	/** @brief Returns the normal of the collision plane
	 */
	glm::vec3 Normal() const;

	/** @brief Sets PointA of the collision
	 *
	 *	@param a The point to assign
	 */
	void PointA(glm::vec3 a);
	
	/** @brief Sets Point B of the collision
	 *
	 *	@param b The point to assign
	 */
	void PointB(glm::vec3 b);
	
	/** @brief Sets the normal to the collision plane
	 *
	 *	@param n The vector normal to the collision plane to assign
	 */
	void Normal(glm::vec3 n);

	/** @brief Returns the depth of collision
	 */
	float Depth() const;
	
	/** @brief Returns if a collision has ocurred
	 */
	bool HasCollision() const;

private:
	glm::vec3 mA;		/*!< Point A of the collision */
	glm::vec3 mB;		/*!< Point B of the collision */
	glm::vec3 mNormal;  /*!< Normal to the plane of the collision */
	float mDepth;		/*!< Depth of the collision */
	bool mHasCollision;	/*!< Flag indicating a collision ocurring */
};

/** @class Collision
 *
 *	@brief Holds information relating a collision, including the point and entities involved
 *
 *	@author Nicholas Subianto
 *	@author Aaron Thomson
 */
class Collision
{
public:
	/** @brief Constructor
	 *
	 *	@param A Entity A in the collision
	 *	@param B Entity B in the collision
	 *	@param point The collision point 
	 */
	Collision(ECS::Entity A, ECS::Entity B, CollisionPoint point);

	/** @brief Returns Entity A
	 */
	ECS::Entity EntityA() const;
	
	/** @brief Returns Entity B
	 */
	ECS::Entity EntityB() const;

	/** @brief Returns the collision point data of the collision
	 */
	CollisionPoint Point() const;

private:
	ECS::Entity mEntityA;	/*!< An entity involved in the collision */
	ECS::Entity mEntityB;	/*!< An entity involved in the collision */
	CollisionPoint mPoint;	/*!< The point data of the collision */
};

/** @class Box */
class Box;
/** @class Sphere */
class Sphere;

/** @class Collider 
 *
 *	@brief Abstract class with functions for testing collisions between different types of derived shapes
 *
 *	@author Nicholas Subianto
 *	@author Aaron Thomson
 */
class Collider
{
public:
	/** @brief Constructor
	 */
	Collider() {};

	/** @brief Returns the inertia tensor of the derived shape 
	 */
	glm::mat3 Inertia();

	/** @brief Tests a collision between another collider shape
	 *
	 *	@param transformA	Transform of entity A
	 *	@param colliderB	Collider of entity B
	 *	@param transformB	Transform of entity B
	 */
	virtual CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Collider* colliderB,
		const Component::com_Transform* transformB) const = 0;

	/** @brief Tests the ocurrence of a collision specifically with a box
	 *
	 *	@param transformA	Tranform of Entity A
	 *	@param colliderB	Box collider of entity B
	 *	@param transformB	Transform of entity B
	 */
	virtual CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Box* colliderB,
		const Component::com_Transform* transformB) const = 0;
		
	/** @brief Tests the ocurrence of a collision specifically against a sphere
	 *
	 *	@param transformA	Transform of entity A
	 *	@param colliderB	Sphere collider of entity B
	 *	@param transformB	Transform of entity B
	 */
	virtual CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Sphere* colliderB,
		const Component::com_Transform* transformB) const = 0;

	/** @brief Override function to set the inertia tensor of a box shape
	 *
	 *	@param mass Mass of the entity
	 */
	virtual void SetInertia(float mass) = 0;

protected:
	glm::mat3 mInertia = glm::mat3(0); /*!< Inertia tensor in every shape */
};

/** @class Box
 *
 *	@brief Derived collider shape. Defines a box shape 
 *
 *	@author Nicholas Subianto
 *	@author Aaron Thomson
 */
class Box 
	: public Collider
{
public:
	/** @brief Constructor
	 */
	Box() {};
	
	/** @brief Constructor
	 *
	 *	@param min The minimum point of the box
	 *	@param max The maximum point of the box
	 */
	Box(glm::vec3 min, glm::vec3 max);

	/** @brief Returns the max point of the box
	 */
	glm::vec3 Max() const;

	/** @brief Returns the min point of the box
	 */
	glm::vec3 Min() const;

	CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Collider* colliderB,
		const Component::com_Transform* transformB) const override;

	CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Box* colliderB,
		const Component::com_Transform* transformB) const override;

	CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Sphere* colliderB,
		const Component::com_Transform* transformB) const override;

	void SetInertia(float mass) override;
		
private:
	glm::vec3 mMin;	/*!< Vector defining the maximum point of the box */
	glm::vec3 mMax;	/*!< Vector defining the minimum point of the box */
};

/** @class Sphere
 *
 *	@brief A sphere shaped collider
 * 
 *	@author Nicholas Subianto
 *	@author Aaron Thomson
 */
class Sphere 
	: public Collider
{
public:
	/** @brief Constructor 
	 */
	Sphere() {};
	
	/** @brief Constructor
	 *	
	 *	@param centre The centre point of the sphere
	 *	@param rad The radius of the sphere
	 */
	Sphere(glm::vec3 center, float rad);

	/** @brief Returns the vector to the centre of the sphere
	 */
	glm::vec3 Center() const;
	
	/** @brief Returns the radius of the sphere
	 */
	float Radius() const;

	CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Collider* colliderB,
		const Component::com_Transform* transformB) const override;

	CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Box* colliderB,
		const Component::com_Transform* transformB) const override;

	CollisionPoint TestCollision(
		const Component::com_Transform* transformA,
		const Sphere* colliderB,
		const Component::com_Transform* transformB) const override;

	void SetInertia(float mass) override;

private:
	glm::vec3 mCenter;	/*<! Vector the centre of the sphere */
	float mRadius;		/*<! Radius of the sphere */
};