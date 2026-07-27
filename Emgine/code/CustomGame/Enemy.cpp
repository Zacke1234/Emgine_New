#include "Enemy.h"

Enemy::Enemy(ObjectManager* aObjectManager, RigidbodyManager* aRigidbodyManager, ColliderManager* aColliderManager, MeshManager* aMeshManager, TextureManager* aTextureManager)
{
	thisObjectManager = aObjectManager;
	thisrbManager = aRigidbodyManager;
	thisColliderManager = aColliderManager;
	thisTexManager = aTextureManager;
	thisMeshManager = aMeshManager;
	sphereColl = new SphereCollider(1.0f, glm::vec3(0));
	EnemyColl = aColliderManager->Create("EnemyColl", sphereColl, false);
	EnemyRB = aRigidbodyManager->Create("EnemyRigidbody", 0.5, false, true);
	EnemyColl->tag = "Enemy";
	enemyMesh = aMeshManager->Create("Cube", "cube.obj");
	enemyTexture = aTextureManager->Create("lila", "lila.png");
	EnemyObj = aObjectManager->Create("Enemy", enemyMesh, enemyTexture, EnemyColl, EnemyRB);
	EnemyObj->Position = glm::vec3(8, 3.5f, 10);
	EnemyObj->Scale = glm::vec3(1);
}

void Enemy::Move()
{
	int randomNumber = rand() % 6;

	switch (randomNumber)
	{
	case 0:
		EnemyRB->force = glm::vec3(2, 0, 0);
			break;

	case 1:
		EnemyRB->force = glm::vec3(0, 1.2f, 0);
		break;

	case 2:
		EnemyRB->force = glm::vec3(0, 0, 2);
		break;

	case 3:
		EnemyRB->force = glm::vec3(-2, 0, 0);
		break;

	case 4:
		EnemyRB->force = glm::vec3(0, 0, -2);
		break;

	case 5:
		EnemyRB->force = glm::vec3(0, -0.5f, 0);
		break;
	}
}
