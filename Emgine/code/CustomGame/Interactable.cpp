#include "Interactable.h"

Interactable::Interactable(ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, Physics* aPhysics)
{
	CubeCollider* cubeColl = new CubeCollider(glm::vec3(1.5f, 1.5f, 1.5f), glm::vec3(0, 0, 0));
	switchtexture = aTextureManager->Find("wall");
	switchMesh = aMeshManager->Create("well", "well.obj");
	switchCollider = aColliderManager->Create("switchCollider", cubeColl);
	
	switchObject = aObjectManager->Create("Switch", switchMesh, switchtexture, switchCollider, NULL);
	switchPhysics = aPhysics;
	switchObject->Position = glm::vec3(4.0f, 10.0f, 8.0f);
	switchCollider->position = switchObject->Position;
	switchCollider->transform = switchObject->trans;
}

bool Interactable::Collided(Collider* PlayerColl)
{

	

	if(switchPhysics->BoolCheckIntersect(switchCollider, PlayerColl))
	{
		return true;
	}
	else
	{
		return false;
	}
}
