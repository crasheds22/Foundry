#pragma once

#include <glm/vec3.hpp>

namespace Component
{
	/** @class com_Transform
	 *
	 *	@brief Acomponent describing the transform of an entity
	 *
	 *	@author Aaron Thomson
	 */
	class com_Transform
	{
	public:
		/** @brief Constructor
		 */
		com_Transform() {};
		
		/** @brief Constructor
		 *
		 *	@param pos Initial position
		 *	@param rot Initial rotations
		 *	@param scale Initial scale
		 */
		com_Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);

		/** @breif Returns the positon
		 */
		glm::vec3 Position() const;
		
		/** @brief Updates the position
		 *
		 *	@param position The new position value
		 */
		void Position(glm::vec3 position);

		/** @brief Returns the rotations
		 */
		glm::vec3 Rotation() const;
		
		/** @brief Updates the rotations
		 *
		 *	@param rotation The new rotation values
		 */
		void Rotation(glm::vec3 rotation);

		/** @brief Returns the scale on each axis
		 */
		glm::vec3 Scale() const;
		
		/** @brief Updates the scale on each axis
		 *
		 *	@param scale The new scale values
		 */
		void Scale(glm::vec3 scale);

		/** @brief Returns the front facing vector
		 */
		glm::vec3 Front() const;
		
		/** @brief Updates the front facing vector
		 *
		 *	@param front The new front vector value
		 */
		void Front(glm::vec3 front);

	private:
		glm::vec3 mPosition{};	/*<! The position	*/
		glm::vec3 mRotation{};	/*<! The rotations about each axis */
		glm::vec3 mScale{};		/*<! The scale on each axis */
		glm::vec3 mFront{};		/*<! The front facing vector */
	};
}
