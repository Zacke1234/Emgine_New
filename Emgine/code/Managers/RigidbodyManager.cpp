#include "Managers/RigidbodyManager.h"

Rigidbody* RigidbodyManager::Create(float gravity)
{
	Rigidbody* rb = new Rigidbody(gravity);
	Rigidbody::rbEntities.push_back(rb);
	return rb;
}
