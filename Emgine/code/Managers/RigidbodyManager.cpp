#include "Managers/RigidbodyManager.h"

Rigidbody* RigidbodyManager::Create(std::string name, float gravity, bool isKinematic, bool hasGrav)
{
	Rigidbody* rb = new Rigidbody();
	rb->name = name;
	rb->gravity = gravity;
	rb->isKinematic = isKinematic;
	rb->hasGravity = true;
	rb->mass = 1;
	Rigidbody::rbEntities.push_back(rb);

	return rb;
}
