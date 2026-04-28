#include "Rigidbody.h"
#include <Physics.h>
std::vector<Rigidbody*> Rigidbody::rbEntities;
//std::vector<Motion*> Rigidbody::motions;
Rigidbody::Rigidbody(float gravity, bool isKinematic)
{
	name = "rigidbody";
	hasGravity = true;
	inverseMomentOfInertia = Math::identity3;
	mass = 0;
	momentOfInertia = Math::identity3;
	velocity = glm::vec3(0, 0, 0);
	transform = Math::identity4;
	angularVelocity = glm::vec3(0, 0, 0);
	position = glm::vec3(0, 0, 0);
	gravity = 0.0f;
	isKinematic = false;

}

MotionCollision::MotionCollision()
{
	origin = glm::vec3(0, 0, 0);
	direction = glm::vec3(0, 0, 0);
	LinearDrag = 0;
	restitution = 0;
}