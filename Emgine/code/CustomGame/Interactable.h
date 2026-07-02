#include <Collider.h>
#include <ObjectManager.h>
#include <TextureManager.h>
#include <ColliderManager.h>
#include <Physics.h>
#include <Object.h>

#pragma once
class Interactable
{
public:

	Interactable();
	Interactable(ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, Physics* aPhysics);

	bool Collided(Collider* PlayerColl);

	
	Physics* getPhysics;
	Texture* getTexture;
	Mesh* getMesh;
	Collider* getCollider;
	Object* getObject;

};


class GoalPost : public Interactable
{
public:
	
	GoalPost(ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, Physics* aPhysics);
	
	bool Collided(Collider* PlayerColl);

	//bool Collided(Collider* playerColl);

};
