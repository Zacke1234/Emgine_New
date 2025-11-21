#include "ColliderManager.h"
Collider* ColliderManager::Create(std::string collName = "new_collider", Collider* myColl = NULL)
{
	
	myColl = new Collider();
	Collider::CollEntities.push_back(myColl);
	return myColl;
}