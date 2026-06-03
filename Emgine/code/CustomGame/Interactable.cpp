#include "Interactable.h"

Interactable::Interactable()
{
}

bool Interactable::Collided(Collider* PlayerColl)
{
	if (PlayerColl != switchCollider)
	{
		return true;
	}
	else
	{
		return false;
	}
}
