#pragma once
/**
* @class Sphere
* @brief Sphere bounding volume
* 
* @author Kristian
*/


#include <glm/glm.hpp>

namespace Component
{
	class Sphere 
	{
	public:
		Sphere(glm::vec3 centre, float rad);
		Sphere(const Sphere& s);
		~Sphere();

		glm::vec3 Centre() const;
		void Centre(glm::vec3 centre);

		float Radius() const;
		void Radius(float radius);

	private:
		glm::vec3 mCentre; // center point
		float mRadius; // radius of sphere
	};
}