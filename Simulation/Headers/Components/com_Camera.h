#pragma once

#include <map>

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Component
{
	/** @enum Direction
	 */
	enum class Direction { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

	/** @class com_Camera
	 *
	 *	@breif A flying camera
	 *
	 *	@author Aaron Thomson
	 */
	class com_Camera
	{
	public:
		/** @brief Constructor
		 */
		com_Camera() {};
		
		/** @brief Constructor
		 *
		 *	@param pos Initial position of the camera
		 *	@param wup World up of the camera
		 *	@param yaw The initial rotation about the y axis
		 *	@param pitch The initial rotation about the x axis
		 */
		com_Camera(glm::vec3 pos, glm::vec3 wup = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

		/** @brief Updates the position of the camera
		 *
		 *	@param position The new position to update to
		 */
		void Position(const glm::vec3 position);

		/** @breif Returns the position of the camera
		 */
		glm::vec3 Position() const;
		
		/** @brief Returns the front vector of the camera
		 */
		glm::vec3 Front() const;
		
		/** @brief Returns the vector at 90degrees to the front vector
		 */
		glm::vec3 Right() const;
		
		/** @brief Returns the cross product vector of the Front and Right vectors
		 */
		glm::vec3 Up() const;
		
		/** @brief Returns the world up vector
		 */
		glm::vec3 WorldUp() const;

		/** @brief Retusn the current rotation about the y axis
		 */
		float Yaw() const;
		
		/** @brief returns the current rotation about the x axis
		 */
		float Pitch() const;
		
		/** @brief Returns the current rotation about the z axis
		 */
		float Roll() const;

		/** @brief Returns a vector composed of the rotations about each axis
		 */
		glm::vec3 Rotations() const;

		/** @brief Returns the current zoom level of the camera
		 */
		float Zoom() const;

		/** @brief Returns the view matrix of the camera
		 */
		glm::mat4 ViewMatrix() const;

		/** @brief Moves the camera in a direction by a velocity
		 *
		 *	@param direction The direction to move in
		 *	@param velocity The amount of move by in a single step
		 */
		void MoveCamera(Direction direction, float velocity);

		/** @brief Rotates the camera about its local axes
		 *
		 *	@param xOffset The amount to rotate about the x axis
		 *	@param yOffset The amount to rotate about the y axis
		 *	@param zOffset The amount to rotate about the z axis
		 *	@param constrainPitch Constrains the pitch to be within -90 and +90 degrees
		 */
		void RotateCamera(float xOffset, float yOffset, float zOffset = 0.0f, bool constrainPitch = true);
		
		/** @brief modifies the zoom level by the specified offset
		 *
		 *	@param yOffset The amount to change the zoom level by
		 */
		void Zoom(float yOffset);

	private:
		glm::vec3 mPosition{};	/*<! The position of the camera */
		glm::vec3 mFront{};		/*<! The front vector of the camera */
		glm::vec3 mRight{};		/*<! The right vector of the camera */
		glm::vec3 mUp{};		/*<! The up vector of the camera */
		glm::vec3 mWorldUp{};	/*<! The world up vector */

		float mYaw{};		/*<! The amount of rotation about the y axis */
		float mPitch{};		/*<! The amount of rotation about the x axis */
		float mRoll{};		/*<! The amount of rotation about the z axis */

		float mZoom{};		/*<! The cameras zoom level */

		std::map<Direction, glm::vec3> DirectionMapper{};	/*<! A map from the direction enum to a vector displacement */

		/** @brief Updates the vectors of the camera whenever the angles change
		 */
		void UpdateCameraVectors();	
		
		/** @brief Updates the direction vecotrs whenever the angles change 
		 */
		void UpdateMapper();
	};
}
