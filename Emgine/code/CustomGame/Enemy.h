#include "Rigidbody.h"
#include "Collider.h"
#include "Object.h"
#include "ColliderManager.h"
#include "RigidbodyManager.h"
#include "ObjectManager.h"
#include "TextureManager.h"
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
	CubeCollider* cubeColl;

	Mesh* enemyMesh;
	Texture* enemyTexture;



	ObjectManager* thisObjectManager;
	RigidbodyManager* thisrbManager;
	ColliderManager* thisColliderManager;
	TextureManager* thisTexManager;
	MeshManager* thisMeshManager;

};

