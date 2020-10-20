#pragma once

#include <map>

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
*	\namespace Component
* 
*	The namespace all Components are located in.
*/
namespace Component
{
	/**
	*	\enum Direction
	* 
	*	Used to represent the direction of motion in an abstract manner.
	*/
	enum class Direction { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

	/**
	*	\class com_Camera
	* 
	*	A component representing a camera in the world.
	*	Contains methods to update view matrix, rotate with input and move.
	*/
	class com_Camera
	{
	public:
		/**
		*	\brief Default constructor
		* 
		*	Not to be used by the user.
		*/
		com_Camera() {};
		/**
		*	\brief Constructor
		* 
		*	\param [in] pos		the initial position of the camera
		*	\param [in] wup		the world up vector
		*	\param [in] yaw		the initial yaw value
		*	\param [in] pitch	the initial pitch value
		* 
		*	\pre No camera object exists
		*	\post A camera object is constructed with the values given as parameters
		*/
		com_Camera(glm::vec3 pos, glm::vec3 wup = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

		/**
		*	\brief Position mutator
		* 
		*	\param [in] position	the new position value
		* 
		*	\post The mPosition value is assigned to position
		*/
		void Position(const glm::vec3 position);

		/**
		*	\brief Position vector accessor
		* 
		*	\return mPosition
		* 
		*	\post The value is returned, but unchanged
		*/
		glm::vec3 Position() const;
		/**
		*	\brief Front vector accessor
		* 
		*	\return mFront
		* 
		*	\post The value is returned, but unchanged
		*/
		glm::vec3 Front() const;
		/**
		*	\brief Right vector accessor
		* 
		*	\return mRight
		* 
		*	\post The value is returned, but unchanged
		*/
		glm::vec3 Right() const;
		/**
		*	\brief Up vector accessor
		* 
		*	\return mUp
		* 
		*	\post The value is returned, but unchanged
		*/
		glm::vec3 Up() const;
		/**
		*	\brief World up vector accessor
		* 
		*	\return mWorldUp
		* 
		*	\post The value is returned, but unchanged
		*/
		glm::vec3 WorldUp() const;

		/**
		*	\brief Yaw value accessor
		* 
		*	\return mYaw
		* 
		*	\post The value is returned, but unchanged
		*/
		float Yaw() const;
		/**
		*	\brief Pitch value accessor
		* 
		*	\return mPitch
		* 
		*	\post The value is returned, but unchanged
		*/
		float Pitch() const;
		/**
		*	\brief Roll value accessor
		* 
		*	\return mRoll
		* 
		*	\post The value is returned, but unchanged
		*/
		float Roll() const;

		/**
		*	\brief A vector representing the rotation values collectively
		*
		*	\return A constructed vector of the three values
		* 
		*	\post A vector with x, y and z components matching the pitch, yaw and roll values respectively is returned
		*/
		glm::vec3 Rotations() const;

		/**
		*	\brief Zoom value accessor
		* 
		*	\return mZoom
		* 
		*	\post The value is returned, but unchanged
		*/
		float Zoom() const;

		/**
		 *	\brief Calculates and constructs the look at matrix
		 *
		 *	\return a constructed matrix from the position, fron and up vectors
		 *
		 *	\post The constructed matrix is returned
		 */
		glm::mat4 ViewMatrix() const;

		/**
		 *	\brief Moves the camera in a desired direction, at a velcotiy
		 *
		 *	\param [in] direction	The direction to move in
		 *	\param [in] velocity	The amount to move in that direction
		 *
		 *	\post The cmaera's position has been updated in the direction, multiplied by the velocity
		 */
		void MoveCamera(Direction direction, float velocity);
		/**
		 *	\brief Rotates the camera by the amounts passed in
		 *
		 *	\param [in] xOffset The amount to rotate around the x axis
		 *	\param [in] yOffset The amount to rotate around the y axis
		 *	\param [in] zOffset The amount to rotate aroudn the z axis
		 *	\param [in] constrainPitch A flag to set to clmap the pitch value between -90 and 90 degrees
		 */
		void RotateCamera(float xOffset, float yOffset, float zOffset = 0.0f, bool constrainPitch = true);
		/**
		 *	\brief Zoom mutator
		 *
		 *	\param [in] yOffset	The amount to change the zoom level by
		 *
		 *	\post The zoom value is updated and clamped between 1.0f and 45.0f
		 */
		void Zoom(float yOffset);

	private:
		glm::vec3 mPosition{};	/*!< The position of the camera in 3D space*/
		glm::vec3 mFront{};		/*!< The front facing vector of the camera*/
		glm::vec3 mRight{};		/*!< The right facing vector of the camera*/
		glm::vec3 mUp{};		/*!< Vector representing the upwards direction of the camera*/
		glm::vec3 mWorldUp{};	/*!< Vector representing the worlds upwards direction*/

		float mYaw{};	/*!< Rotation of the camera about the Y axis*/
		float mPitch{};	/*!< Rotation of the camera about the X axis*/
		float mRoll{};	/*!< Rotation of the camera about the Z axis*/

		float mZoom{};	/*!< Zoom level of the camera*/

		std::map<Direction, glm::vec3> DirectionMapper{};	/*!< A way to store the mappings between direction and a vector*/

		/**
		*	\brief Update the camera's vector
		* 
		*	\post The camera's vectors are updated appropriately
		*/
		void UpdateCameraVectors();
		/**
		*	\brief Updates the direction map vectors
		* 
		*	\post The DirectionMapper values have been updated to reflect the new direction vectors
		*/
		void UpdateMapper();
	};
}
