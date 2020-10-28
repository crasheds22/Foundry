#pragma once

#include <glm/glm.hpp>
#include <glm/geometric.hpp>

/**	@class Physics
 *
 *	@brief A class for functions related to the operation of physics
 * 
 *	@author Nicholas Subianto
 */
class Physics
{
public:
	/**	@brief Calculates the total restitution of the two bodies
	 *
	 *	@return float
	 *	@param resA	Restitution value of body A
	 *	@param resB	Restitution value of body B
	 */
	static float CalculateRestitution(float resA, float resB);

	/** @brief Calculates the difference of the velocities of the bodies colliding
	 *
	 *	@return float
	 *	@param normal	The vector indicating the normal of the collision
	 *	@param vA		The velocity of body A
	 *	@param vB		The velocity of body B
	 */
	static float CalculateVelocityDifference(glm::vec3 normal, glm::vec3 vA, glm::vec3 vB);

	/**	@brief Calculates the amount a body has rotated about an axis
	 *
	 *	@return float
	 *	@param rotVel	Rotational velocity of the body
	 *	@param radius	Vector radius from the collision normal
	 *	@param normal	The collision normal
	 */
	static float CalculateAngleAround(glm::vec3 rotvel, glm::vec3 radius, glm::vec3 normal);

	/**	@brief A partial calculation for physics resolution
	 *
	 *	@return float
	 *	@param radius	The vector radius from the collision normal
	 *	@param normal	The collision normal
	 *	@param inertia	The inertia tensor of the body collidding
	 */
	static float CalculateBeast(glm::vec3 radius, glm::vec3 normal, glm::mat3 inertia);
	
	/**	@brief	Calculates the radius from the collision points to the centre of mass of a body
	 *
	 *	@return glm::vec3
	 *	@param pA		Point A of the collision
	 *	@param pB		Point B of the collision
	 *	@param com		Centre of mass of the body
	 *	@param worldPos	World position of the body
	 */
	static glm::vec3 CalculateRadius(glm::vec3 pA, glm::vec3 pB, glm::vec3 com, glm::vec3 worldPos);

	/**	@brief Calculates the linear velocity after a collision
	 *
	 *	@return glm::vec3
	 *	@param ivelocity	The initial velocity, pre collision
	 *	@param lambda		The lambda value of the collision
	 *	@param mass			The mass of the body
	 *	@param normal		The collision normal
	 */
	static glm::vec3 CalculateCollisionVel(glm::vec3 ivelocity, float lambda, float mass, glm::vec3 normal);
	
	/**	@brief Calculates the rotational velocity after a collision
	 *
	 *	@return glm::vec3
	 *	@param	irotvel		The initial rotational velocity, pre collision
	 *	@param	lambda		The lambda value of the collision
	 *	@param	inertia		The inertia tensor of the body
	 *	@param	radius		The radius from the collision normal
	 *	@param	normal		The collision normal
	 */
	static glm::vec3 CalculateCollisionRotVel(glm::vec3 irotvel, float lambda, glm::mat3 inertia, glm::vec3 radius, glm::vec3 normal);

	/**	@brief	Applies friction to the body's velocity
	 *
	 *	@return glm::vec3
	 *	@param ivelocity	The intial velocity of the body
	 */
	static glm::vec3 ApplyFriction(glm::vec3 ivelocity);
};

