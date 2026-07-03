#include "Interactable.h"

Interactable::Interactable()
{
	//
}

Interactable::Interactable(ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, Physics* aPhysics)
{
	CubeCollider* cubeColl = new CubeCollider(glm::vec3(1.5f, 1.5f, 1.5f), glm::vec3(0, 0, 0));
	getTexture = aTextureManager->Find("wall");
	getMesh = aMeshManager->Create("well", "well.obj");
	getCollider = aColliderManager->Create("switchCollider", cubeColl);
	
	getObject = aObjectManager->Create("Switch", getMesh, getTexture, getCollider, NULL);
	getPhysics = aPhysics;
	//getObject->Position = glm::vec3(4.0f, 10.0f, 8.0f);
	getCollider->position = getObject->Position;
	getCollider->transform = getObject->trans;
}

GoalPost::GoalPost(ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, Physics* aPhysics)
{
	CubeCollider* cubeColl = new CubeCollider(glm::vec3(1.5f, 1.5f, 1.5f), glm::vec3(0, 0, 0));
	getTexture = aTextureManager->Find("goal");
	getMesh = aMeshManager->Create("cube", "cube.obj");
	getCollider = aColliderManager->Create("goalCollider", cubeColl);

	getObject = aObjectManager->Create("GoalPost", getMesh, getTexture, getCollider, NULL);
	getPhysics = aPhysics;
	//getObject->Position = glm::vec3(4.0f, 7.0f, 8.0f);
	getCollider->position = getObject->Position;
	getCollider->transform = getObject->trans;
}

bool GoalPost::Collided(Collider* PlayerColl)
{
	if (getPhysics->BoolCheckIntersect(getCollider, PlayerColl))
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool Interactable::Collided(Collider* PlayerColl)
{

	

	if(getPhysics->BoolCheckIntersect(getCollider, PlayerColl))
	{
		return true;
	}
	else
	{
		return false;
	}
}


