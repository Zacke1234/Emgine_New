#pragma once
#include <string>
#include <Collider.h>
class ColliderManager
{
public:
	Collider* Create(std::string collName, Collider* myColl);
	CubeCollider* cubeColl;
	SphereCollider* sphereColl;
};

