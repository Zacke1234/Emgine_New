#include "Rigidbody.h"
#include "Collider.h"
#include "Object.h"
#include "Managers/ColliderManager.h"
#include "Managers/RigidbodyManager.h"
#include "Managers/ObjectManager.h"
#include "Managers/TextureManager.h"
#include "cstdlib"

#pragma once
class Enemy
{
public: 
	Enemy(ObjectManager* aObjectManager, RigidbodyManager* aRigidbodyManager, ColliderManager* aColliderManager, MeshManager* aMeshManager, TextureManager* aTextureManager);

	void Init();

	void Move();


	Object* EnemyObj;
	Rigidbody* EnemyRB;
	Collider* EnemyColl;
	SphereCollider* sphereColl;

	Mesh* enemyMesh;
	Texture* enemyTexture;



	ObjectManager* thisObjectManager;
	RigidbodyManager* thisrbManager;
	ColliderManager* thisColliderManager;
	TextureManager* thisTexManager;
	MeshManager* thisMeshManager;

};

