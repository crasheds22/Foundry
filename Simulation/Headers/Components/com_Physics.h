#pragma once

#include <glm/glm.hpp>

#include "ECS/Types.h"

#include "Components/com_Transform.h"
#include "Components/Collider.h"

namespace Component
{
	/** @class com_Physics
	 *
	 *	@brief Component containing all physical properties
	 *
	 *	@author Nicholas Subianto
	 */
	class com_Physics
	{
	public:
		/** @brief Constructor
		 */
		com_Physics() {};

		/** @brief Constructor
		 *
		 *	@param mass Mass of the object
		 *	@param res Restitution coefficient of the object (between 0 and 1)
		 *	@param width Width dimension of object
		 *	@param height Height dimension of object
		 *	@param depth Depth dimension of object
		 *	@param dynamic Integer classification of object type (dynamic, static, floor, wall)
		 *	@param coll Collider object, specified bounding volume to be tied to physics.
		 */
		com_Physics(float mass, float res, int width, int height, int depth, int dynamic, Collider* coll);

		/** @brief Returns the Velocity of the object
		 */
		glm::vec3 Velocity() const;

		/** @brief Returns the Acceleration of the object
		 */
		glm::vec3 Acceleration() const;

		/** @brief Returns the Rotational Velocity of the object
		 */
		glm::vec3 RotationVel() const;

		/** @brief Returns the Rotational Acceleration of the object
		 */
		glm::vec3 RotationAcc() const;

		/** @brief Updates the object velocity
		 *
		 *  @param vel the new velocity value
		 */
		void Velocity(glm::vec3 vel);

		/** @brief Updates the object acceleration
		 *
		 *  @param acc the new acceleration value
		 */
		void Acceleration(glm::vec3 acc);

		/** @brief Updates the object rotational velocity
		 *
		 *  @param rotvel the new rotational velocity value
		 */
		void RotationVel(glm::vec3 rotvel);

		/** @brief Updates the object rotational acceleration
		 *
		 *  @param rotacc the new rotational acceleration value
		 */
		void RotationAcc(glm::vec3 rotacc);

		/** @brief Returns the mass of the object
		 */
		float Mass() const;

		/** @brief Returns the inverted mass of the object
		 */
		float InvMass() const;

		/** @brief Returns the restitution coefficient of the object
		 */
		float Restitution() const;

		/** @brief Returns the centre of mass coordinates of the object
		 */
		glm::vec3 CentreOfMass() const;

		/** @brief Returns the object collider
		 */
		Collider* Collidercom() const;

		/** @brief Returns the dynamic type of the object (Dynamic, Static, Floor, Wall)
		 */
		int Dynamic() const;

	private:
		glm::vec3 mVelocity{};		 /*<! The velocity of the object	*/
		glm::vec3 mAcceleration{};	 /*<! The acceleration of the object	*/
		glm::vec3 mRotationVel{};	 /*<! The rotational velocity of the object	*/
		glm::vec3 mRotationAcc{};	 /*<! The rotational acceleration	*/

		float mMass{};				 /*<! The mass of the object	*/
		float mInvMass{};			 /*<! The inverted mass of the object	*/
		float mRestitution{};		 /*<! The coefficient of restitution of the object	*/

		glm::vec3 mCentreOfMass{};	 /*<! The coordinate centre of mass of the object	*/

		Collider* mCollidercom;		 /*<! The object's collider	*/

		int mDynamic;				 /*<! The dynamic type of the object	*/
	};
}