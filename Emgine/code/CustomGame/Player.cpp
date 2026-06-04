#include "Player.h"
#include <iostream>




using namespace std;



Player::Player(GLFWwindow* getWindow, ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager, CameraManager* aCamManager, Time* aTime)
{
	
	//getShader = aShaderManager->DefaultShader;
	getTime = aTime;
	window = getWindow;
	playerMesh = aMeshManager->Create("fish", "fish.obj");
	defaultTex = aTextureManager->Create("default", "Default 1.png");

	SphereCollider* PlayerColl = new SphereCollider(1.5f, glm::vec3(0,0,0));
	playerColl = aColliderManager->Create("Sphere", PlayerColl);
	playerRB = aRigidbodyManager->Create("playerRB", 0.5, true, true);
	playerController = new Controller();
	
	player = aObjectManager->Create("Player", playerMesh, defaultTex, playerColl, playerRB);
	dashStrength = 1.0f;
	jumpHeight = 4.0f;
	movementSpeed = 1.0f;

	playerCamera = aCamManager->Create("PlayerCamera", window);

	playerCamera->fieldOfView = 80.0f;
	playerCamera->sensitivity = 0.1f;
	
	// How to get a functional camera for the player?
}

void Player::InputMovement()
{
	if(playerController->W_KEY(window))
	{
		player->Position += glm::vec3(0.0f, 0.0f, movementSpeed);
	}

	if (playerController->S_KEY(window))
	{
		player->Position += glm::vec3(0.0f, 0.0f, -movementSpeed);
	}

	if (playerController->D_KEY(window))
	{
		player->Position += glm::vec3(movementSpeed, 0.0f, 0.0f);
	}

	if (playerController->A_KEY(window))
	{
		player->Position += glm::vec3(-movementSpeed, 0.0f, 0.0f);
	}

	if (playerController->SPACE_KEY(window))
	{
		if (onGround)
		{
			player->Position += glm::vec3(0.0f, jumpHeight, 0.0f);
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
	
	playerCamera->myPosition = player->Position + glm::vec3(0.0 ,3.0, -0.2);

	
}

void Player::CheckGround()
{
	
}

