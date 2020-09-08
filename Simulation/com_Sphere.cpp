#include "com_Sphere.h"

namespace Component
{
	Sphere::Sphere(glm::vec3 centre, float rad) : mCentre(centre), mRadius(rad)
	{
		Type(ColliderType::SPHERE);
	}

	Sphere::Sphere(const Sphere& s) : mCentre(s.mCentre), mRadius(s.mRadius)
	{
		Type(ColliderType::SPHERE);
	}
	
	Sphere::~Sphere()
	{
	}
	
	glm::vec3 Sphere::Centre() const
	{
		return mCentre;
	}
	
	void Sphere::Centre(glm::vec3 centre)
	{
		mCentre = centre;
	}
	
	float Sphere::Radius() const
	{
		return mRadius;
	}
	
	void Sphere::Radius(float radius)
	{
		mRadius = radius;
	}
}
