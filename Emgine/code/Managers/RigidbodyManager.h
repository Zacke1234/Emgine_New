
#pragma once
#include "Rigidbody.h"



class RigidbodyManager
{
public:

	Rigidbody* Create(std::string name, float gravity = 0.0f, bool isKinematic = false, bool hasGrav = true);
	
};

