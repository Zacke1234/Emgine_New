#include "Player.h"
#include <iostream>




using namespace std;



Player::Player(GLFWwindow* getWindow, ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager, CameraManager* aCamManager, Time* aTime, Physics* aPhysics)
{

	//getShader = aShaderManager->DefaultShader;
	getTime = aTime;
	window = getWindow;
	playerMesh = aMeshManager->Create("fish", "fish.obj");
	defaultTex = aTextureManager->Create("default", "Default 1.png");

	SphereCollider* PlayerColl = new SphereCollider(1.5f, glm::vec3(0, 0, 0));
	playerColl = aColliderManager->Create("PlayerSphere", PlayerColl);
	playerRB = aRigidbodyManager->Create("playerRB", 1.5, true, true);
	playerController = new Controller();

	player = aObjectManager->Create("Player", playerMesh, defaultTex, playerColl, playerRB);
	dashStrength = 1.0f;
	jumpStrength = 4.0f;
	movementSpeed = 10.0f;
	player->Position = glm::vec3(-2, 4, -2);
	playerCamera = aCamManager->Create("PlayerCamera", window);

	playerCamera->fieldOfView = 80.0f;
	playerCamera->sensitivity = 0.1f;

	playerPhysics = aPhysics;

	playerController->glfwSetInputMode_cursor(window);
	playerController->glfwSetInputMode_disabled(window);

	//playerController->Controller_glfwSetKeyCallBack(window);

	// How to get a functional camera for the player?
}


bool wkeyCallBack = false;
bool akeyCallBack = false;
bool skeyCallBack = false;
bool dkeyCallBack = false;

void Player::InputMovement()
{
	playerCamera->myPosition = player->Position + glm::vec3(0.0, 3.0, -0.2);

	player->Rotation = playerCamera->myDirection;

	float xSpeed = playerRB->force.x;
	float zSpeed = playerRB->force.z;
	// acceleration and max acceleration
	
	if (xSpeed > 2)
	{
		playerRB->force.x = 2;
	}

	if (zSpeed > 2)
	{
		playerRB->force.z = 2;
	}
	/*printf("xforce: %4.2f %+.0e %E \n", playerRB->force.x);
	printf("zforce: %4.2f %+.0e %E \n", playerRB->force.z);

	printf("xVelocity: %4.2f %+.0e %E \n", playerRB->velocity.x);
	printf("zVelocity: %4.2f %+.0e %E \n", playerRB->velocity.z);*/

	if (playerController->W_KEY(window))
	{
		// playerCamera->myDirection*
		playerRB->force += movementSpeed * playerRB->direction * getTime->Deltatime;
		wkeyCallBack = true;
		
	}

	if (playerController->W_KEY_RELEASE(window) && wkeyCallBack)
	{
		playerRB->force *= 0.0f * playerRB->direction;
		wkeyCallBack = false;
	}
	 
	if (playerController->S_KEY(window))
	{
		playerRB->force -= movementSpeed * playerRB->direction * getTime->Deltatime;
		skeyCallBack = true;
	}

	if (playerController->S_KEY_RELEASE(window) && skeyCallBack)
	{
		playerRB->force *= 0.0f * playerRB->direction;
		skeyCallBack = false;
	}

	if (playerController->D_KEY(window))
	{
		playerRB->force -= movementSpeed * playerRB->right * getTime->Deltatime;
		dkeyCallBack = true;
	}

	if (playerController->D_KEY_RELEASE(window) && dkeyCallBack)
	{
		playerRB->force *= 0.0f * playerRB->direction;
		dkeyCallBack = false;
	}

	if (playerController->A_KEY(window))
	{
		playerRB->force += movementSpeed * playerRB->right * getTime->Deltatime;
		akeyCallBack = true;
		
	}

	if (playerController->A_KEY_RELEASE(window) && akeyCallBack)
	{
		playerRB->force *= 0.0f * playerRB->direction;
		akeyCallBack = false;
	}

	if (playerController->SPACE_KEY(window))
	{
		if (onGround)
		{
			playerRB->force += glm::vec3(0.0f, jumpStrength, 0.0f); // worst jump in history
			onGround = false;
		}
	}

	if (playerController->ESCAPE_KEY(window))
	{
		playerCamera->TabbedIn = false;
		playerController->glfwSetInputMode_normal(window);
	}

	if (playerController->TAB_KEY(window))
	{
		playerCamera->TabbedIn = true;
		playerController->glfwSetInputMode_cursor(window);
		playerController->glfwSetInputMode_disabled(window);
	}
	
	getShader = aShaderManager->DefaultShader;
	
	
}

void Player::CheckCollision()
{
	for (auto& colls : Collider::CollEntities)
	{
		if (colls != playerColl)
		{
			if (playerPhysics->BoolCheckIntersect(colls, playerColl))
			{
				onGround = true;

			}
			
		}
		
	}


}

