#include "Player.h"
#include <iostream>

using namespace std;



Player::Player(GLFWwindow* getWindow, ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager)
{
	window = getWindow;
	fish = aMeshManager->Create("Fish", "fish.obj");
	defaultTex = aTextureManager->Create("default", "Default 1.png");
	aColliderManager->Create("Sphere");
	playerRB = aRigidbodyManager->Create("playerRB", 0.5, true, true);

	aObjectManager->Create("Player", fish, defaultTex, playerColl, playerRB);
	dashStrength = 0.0f;
	jumpHeight = 0.0f;
	movementSpeed = 0.0f;
	
	

	//myObjectManager->Create("Player", NULL, NULL, NULL, NULL);
}

void Player::InputMovement()
{
	//playerRB->velocity += glm::vec3(0.0f, 0.0f, 1.0f);
	// 
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	//{
	//	//cout << "forward" << endl;
	//	// forward
	//}
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	//{
	//	// backwards
	//}
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	//{
	//	// right
	//}
	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	//{
	//	// left
	//}
}

 // opengl header already inluded error , remove previous include