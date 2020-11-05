#pragma once

#include <glm/glm.hpp>
#include <glm/geometric.hpp>

#include "Components/Collider.h"


/**	@class CollisionAlgo
 *	
 *	@brief A class for static collision detection algorithms
 * 
 *	@author Nicholas Subianto
 */
class CollisionAlgo
{
public:
	/** @brief A static function returning the collision points between two spheres
	 *
	 *	@return The points of collision between the two bodies
	 * 
	 *	@param sA	A pointer to the first sphere body
	 *	@param tA	A pointer to the first body's transform
	 *	@param sB	A pointer to the second sphere body
	 *	@param tB	A pointer to the second body's transform
	 */
	static CollisionPoint FindSphereSphere(
		const Sphere* sA, const Component::com_Transform* tA,
		const Sphere* sB, const Component::com_Transform* tB);

	/**	@brief A static function returning the collision points between a sphere and a box
	 *
	 *	@return The points of collision between the two bodies
	 * 
	 *	@param sA	A pointer to the first sphere body
	 *	@param tA	A pointer to the first body's transform
	 *	@param bB	A pointer to the second box body
	 *	@param tB	A pointer to the second body's transform
	 */
	static CollisionPoint FindSphereBox(
		const Sphere* sA, const Component::com_Transform* tA,
		const Box* bB,	 const Component::com_Transform* tB);

	/** @brief A static function returning the collision points between two boxes
	 *	
	 *	@return The points of collision between the two bodies
	 * 
	 *	@param bA	A pointer to the first box body
	 *  @param tB	A pointer to the first body's transform
	 *	@param bB	A pointer to the second box body
	 *  @param tB	A pointer to the second body's transform
	 */
	static CollisionPoint FindBoxBox(
		const Box* bA, const Component::com_Transform* tA,
		const Box* bB, const Component::com_Transform* tB);
	
private:
	/**	@brief Returns the closest likely point of collision on a box
	 *
	 *	@return The vector representing the closest point of collision
	 * 
	 *	@param point	The point being checked against
	 *  @param max		The maximum point for comparison
	 *	@param min		The minimum point for comparison
	 */
	static glm::vec3 ClampAABB(glm::vec3 point, glm::vec3 max, glm::vec3 min);
};

