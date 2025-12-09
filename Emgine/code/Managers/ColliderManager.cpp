#include "ColliderManager.h"
Collider* ColliderManager::Create(std::string collName = "new_collider", Collider* myColl = NULL)
{ //  ColliderType* collType = NULL
	
	// find scale pos and set the extents?
	myColl = new Collider();
	
	myColl->CollType = myColl->Cube;
	Collider::CollEntities.push_back(myColl);
	return myColl;
}