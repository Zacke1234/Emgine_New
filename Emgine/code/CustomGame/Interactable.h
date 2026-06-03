#include <Collider.h>
#pragma once
class Interactable
{
public:
	Interactable();

	bool Collided(Collider* PlayerColl);

	Collider* switchCollider;


};

