#include "Player.h"
#include <iostream>

using namespace std;



Player::Player(GLFWwindow* getWindow, ObjectManager* aObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager)
{
	Object* aObj;
	Mesh* fish = aMeshManager->Create("Fish", "fish.obj");
	Texture* defaultTex = aTextureManager->Create("default", "Default 1.png");
	Collider* playerColl = aColliderManager->Create("Sphere");
	Rigidbody* playerRB = aRigidbodyManager->Create("playerRB", 0.5, true, true);

	aObjectManager->Create("Player", fish, defaultTex, playerColl, playerRB);
	dashStrength = 0.0f;
	jumpHeight = 0.0f;
	movementSpeed = 0.0f;
	window = getWindow;
	

	//myObjectManager->Create("Player", NULL, NULL, NULL, NULL);
}

void Player::InputMovement()
{
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