#include "Interactable.h"

Interactable::Interactable(ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager)
{
	switchtexture = aTextureManager->Find("wall");
	switchMesh = aMeshManager->Create("well", "well.obj");
	switchCollider = aColliderManager->Create("Sphere");
	switchObject = aObjectManager->Create("Switch", switchMesh, switchtexture, switchCollider, NULL);
	
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
