#include "Managers/RigidbodyManager.h"

Rigidbody* RigidbodyManager::Create(float gravity, bool isKinematic, bool hasGrav)
{
	Rigidbody* rb = new Rigidbody();
	rb->gravity = 0.9;
	rb->isKinematic = isKinematic;
	rb->hasGravity = true;
	rb->mass = 1;
	Rigidbody::rbEntities.push_back(rb);
	//rb->name = "rigidbody";
	return rb;
}
