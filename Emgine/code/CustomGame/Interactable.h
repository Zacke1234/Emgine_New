#include <Collider.h>
#include <ObjectManager.h>
#include <TextureManager.h>
#include <ColliderManager.h>
#pragma once
class Interactable
{
public:
	Interactable(ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager);

	bool Collided(Collider* PlayerColl);

	

	Texture* switchtexture;
	Mesh* switchMesh;
	Collider* switchCollider;
	Object* switchObject;

};

