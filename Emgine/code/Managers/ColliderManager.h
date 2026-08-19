#pragma once
#include <string>
#include <Object.h>
#include <Collider.h>
#include <Managers/ObjectManager.h>

class ColliderManager
{
public:
	Collider* Create(std::string collName, Collider* aCollider = NULL, bool isKinematic = NULL);
	Collider* Find(std::string collName);
};

