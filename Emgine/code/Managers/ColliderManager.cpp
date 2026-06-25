#include "ColliderManager.h"


Collider* ColliderManager::Create(std::string collName = "new_collider", Collider* aCollider, bool isKinematic)
{
	glm::vec3 test = { 1.0f,1.0f,1.0f };
	
	if (!aCollider)
	{
	
		aCollider = new Collider();
		
		aCollider = new CubeCollider(test, glm::vec3(0,0,0));

	}
	
	
	
	aCollider->name = collName;
	aCollider->autoColliderSize = true;
	
	
	
	

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
