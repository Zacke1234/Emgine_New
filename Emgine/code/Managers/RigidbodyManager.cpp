#include "Managers/RigidbodyManager.h"

Rigidbody* RigidbodyManager::Create(float gravity, bool isKinematic, bool hasGrav)
{
	Rigidbody* rb = new Rigidbody(gravity, isKinematic);
	rb->gravity = gravity;
	rb->isKinematic = isKinematic;
	rb->hasGravity = hasGrav;
	rb->mass = 1;
	Rigidbody::rbEntities.push_back(rb);
	//rb->name = "rigidbody";
	return rb;
}
