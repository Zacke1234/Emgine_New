#include "Rigidbody.h"
#include <Physics.h>
std::vector<Rigidbody*> Rigidbody::rbEntities;

Rigidbody::Rigidbody(float gravity)
{
	gravity = 9.84f;
	hasGravity = true;
	inverseMomentOfInertia = Math::identity3;
	mass = 0;
	momentOfInertia = Math::identity3;
	velocity = glm::vec3(0, 0, 0);
	transform = Math::identity4;
	angularVelocity = glm::vec3(0, 0, 0);
	isKinematic = false;
}
