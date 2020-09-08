#include "com_Sphere.h"

namespace Component
{
	Sphere::Sphere(glm::vec3 center, float rad) : mCenter(center), mRadius(rad)
	{
		Type(ColliderType::SPHERE);
	}

	Sphere::Sphere(const Sphere& s) : mCenter(s.mCenter), mRadius(s.mRadius)
	{
		Type(ColliderType::SPHERE);
	}
	
	Sphere::~Sphere()
	{
	}
	
	glm::vec3 Sphere::Center() const
	{
		return mCenter;
	}
	
	void Sphere::Center(glm::vec3 center)
	{
		mCenter = center;
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
