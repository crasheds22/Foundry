#include "com_Collider.h"

namespace Component
{
	Collider::Collider() {
	} // end Collider

	Collider::~Collider() {

	} // end ~Collider

	void Collider::Type(ColliderType type) {
		mType = type;
	} // end Type

	ColliderType Collider::Type() {
		return(mType);
	} // end Type
}