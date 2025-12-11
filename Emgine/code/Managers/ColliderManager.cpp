#include "ColliderManager.h"
Collider* ColliderManager::Create(std::string collName = "new_collider", Collider* myColl = NULL)
{ //  ColliderType* collType = NULL

	//myColl = new Collider();
	
	
	// find scale pos and set the extents?
	
	myColl->name = collName;
	//myColl->CollType = myColl->Cube;
	Collider::CollEntities.push_back(myColl);
	
	return myColl;
}


// I want Sphere collider and cube collider to be part of the Collider class type
// 