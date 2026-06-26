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
	Interactable(ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, Physics* aPhysics);

	bool Collided(Collider* PlayerColl);

	
	Physics* switchPhysics;
	Texture* switchtexture;
	Mesh* switchMesh;
	Collider* switchCollider;
	Object* switchObject;

};

