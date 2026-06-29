#include "Enemy.h"

Enemy::Enemy(ObjectManager* aObjectManager, RigidbodyManager* aRigidbodyManager, ColliderManager* aColliderManager, MeshManager* aMeshManager, TextureManager* aTextureManager)
{
	thisObjectManager = aObjectManager;
	thisrbManager = aRigidbodyManager;
	thisColliderManager = aColliderManager;
	thisTexManager = aTextureManager;
	thisMeshManager = aMeshManager;
	cubeColl = new CubeCollider(glm::vec3(2.0f), glm::vec3(0.0));
	EnemyColl = aColliderManager->Create("EnemyCollider", cubeColl, false);
	EnemyRB = aRigidbodyManager->Create("EnemyRigidbody", 0.5, false, true);
	EnemyColl->tag = "Enemy";
	enemyMesh = aMeshManager->Create("fish", "fish.obj");
	enemyTexture = aTextureManager->Create("wall", "wall.jpg");
	EnemyObj = aObjectManager->Create("Enemy", enemyMesh, enemyTexture, EnemyColl, EnemyRB);
	EnemyObj->Position = glm::vec3(8, 2, 10);
}

void Enemy::Move()
{
	int randomNumber = rand() % 6;

	switch (randomNumber)
	{
	case 0:
		EnemyRB->force = glm::vec3(1, 0, 0);
			break;

	case 1:
		EnemyRB->force = glm::vec3(0, 1, 0);
		break;

	case 2:
		EnemyRB->force = glm::vec3(0, 0, 1);
		break;

	case 3:
		EnemyRB->force = glm::vec3(-1, 0, 0);
		break;

	case 4:
		EnemyRB->force = glm::vec3(0, 0, -1);
		break;

	case 5:
		//EnemyRB->force = glm::vec3(-1, -1, -1);
		break;
	}
}
