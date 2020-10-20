#pragma once

#include <glm/vec3.hpp>

/**	\namespace Component
 *
 *	The namespace all Components are located in.
 */
namespace Component
{
	/**
	*	\class com_Transform
	* 
	*	\brief Class to hold all information about transforms
	*/
	class com_Transform
	{
	public:
		/**
		*	\brief Default constructor
		* 
		*	Not to be used by the user
		* 
		*	\post com_Transform is constructed
		*/
		com_Transform() {};
		/**
		*	\brief Constructor
		* 
		*	\param [in] pos		initial position of transform
		*	\param [in] rot		initial rotation of transform
		*	\param [in] scale	scale of transform
		*/
		com_Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);

		/**
		*	\brief Position accessor
		* 
		*	\return mPosition
		*	\post mPosition is returned, but unchanged
		*/
		glm::vec3 Position() const;
		/**
		*	\brief Position mutator
		* 
		*	\param [in] position	value to assign to mPosition
		* 
		*	\post mPosition is made equal to position
		*/
		void Position(glm::vec3 position);

		/**
		*	\brief Rotation accessor
		* 
		*	\return mRotation
		*	\post mRotation is returned, but unchanged
		*/
		glm::vec3 Rotation() const;
		/**
		*	\brief Rotation mutator
		* 
		*	\param [in] rotation	value to assign to mRotation
		* 
		*	\post mRotation is made equal to rotation
		*/
		void Rotation(glm::vec3 rotation);

		/**
		*	\brief Scale accessor
		* 
		*	\return mScale
		*	\post mScale is returned, but unchanged
		*/
		glm::vec3 Scale() const;
		/**
		*	\brief Scale mutator
		* 
		*	\param [in] scale	value to assign to mScale
		* 
		*	\post mScale is made equal to scale
		*/
		void Scale(glm::vec3 scale);

	private:
		glm::vec3 mPosition{};	/*!< position of transform*/
		glm::vec3 mRotation{};	/*!< rotation of transform*/
		glm::vec3 mScale{};		/*!< scale of transform*/
	};
}
