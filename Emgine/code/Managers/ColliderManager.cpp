#include "ColliderManager.h"


Collider* ColliderManager::Create(std::string collName = "new_collider")
{
	glm::vec3 test = { 1.0f,1.0f,1.0f };
	Collider* myColl = new Collider();
	myColl->name = collName;

	

	if (collName == "Cube")
	{
		
		
		myColl = new CubeCollider(test, test, test);
		
	}
	if (collName == "Sphere")
	{
		myColl = new SphereCollider(test, 1.0f, test);
		
	}
	else
	{
		std::cout << "other collider" << std::endl;
	}
	

	Collider::CollEntities.push_back(myColl);
	
	return myColl;
}

