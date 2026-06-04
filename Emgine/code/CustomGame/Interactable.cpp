#include "Interactable.h"

Interactable::Interactable(ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, Physics* aPhysics)
{
	switchtexture = aTextureManager->Find("wall");
	switchMesh = aMeshManager->Create("well", "well.obj");
	switchCollider = aColliderManager->Create("Cube");
	switchObject = aObjectManager->Create("Switch", switchMesh, switchtexture, switchCollider, NULL);
	switchPhysics = aPhysics;
	switchObject->Position = glm::vec3(4.0f, 1.0f, 4.0f);
}

bool Interactable::Collided(Collider* PlayerColl)
{
	if(switchPhysics->BoolCheckIntersect(PlayerColl, switchCollider))
	{
		return true;
	}
	else
	{
		return false;
	}
}
