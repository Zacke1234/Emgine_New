#include "ColliderManager.h"


Collider* ColliderManager::Create(std::string collName = "new_collider", Collider* aCollider, bool isKinematic)
{
	glm::vec3 test = { 1.0f,1.0f,1.0f };
	
	if (aCollider == NULL)
	{
		
		aCollider = new Collider();
		
		
		if (collName == "Cube" && !aCollider)
		{

			
			aCollider = new CubeCollider(test, test);

		}
		if (collName == "Sphere" && !aCollider)
		{
			aCollider = new SphereCollider(1.0f, test);

		}
		else
		{
			std::cout << "other collider" << std::endl;
		}
	}
	aCollider->isKinematic = isKinematic;
	aCollider->autoColliderSize = true;
	
	aCollider->name = collName;

	

	
	

	Collider::CollEntities.push_back(aCollider);
	
	return aCollider;
}

Collider* ColliderManager::Find(std::string collName)
{
	for (Collider* colliders : Collider::CollEntities)
	{
		if (colliders->name == collName)
		{
			return colliders;
		}
	}
}
