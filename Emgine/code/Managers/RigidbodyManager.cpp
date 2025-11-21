#include "Managers/RigidbodyManager.h"

Rigidbody* RigidbodyManager::Create(float gravity)
{
	Rigidbody* rb = new Rigidbody(gravity);
	return rb;
}
