#pragma once
#include <string>
#include <Object.h>
#include <Collider.h>
#include <ObjectManager.h>

class ColliderManager
{
public:
	Collider* Create(std::string collName);

};

