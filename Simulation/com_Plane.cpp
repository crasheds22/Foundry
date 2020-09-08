#include "com_Plane.h"

namespace Component
{
	Plane::Plane(glm::vec3 v, glm::vec3 n) {
		vec = v;
		normal = n;
	} // end Plane

	Plane::Plane(const Plane& p) {
		vec = p.vec;
		normal = p.normal;
	} // end Plane
}