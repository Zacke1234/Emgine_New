#include "MainGameplay.h"



void MainGameplay::Initialise(GLFWwindow* getWindow, ObjectManager* myObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager, CameraManager* aCamManager, Time* aTime, ShaderManager* aShaderManager, Physics* aPhysics) // runs once when initialising the game
{
	
	iSwitch = new Interactable(myObjectManager, aMeshManager, aTextureManager, aColliderManager, aPhysics);
	player = new Player(getWindow, myObjectManager, aMeshManager, aTextureManager, aColliderManager, aRigidbodyManager, aCamManager, aTime, aPhysics);

	SphereCollider* sphere = new SphereCollider(1.0f, glm::vec3(0, 0, 0));
	Collider* doorColl;
	CubeCollider* cube = new CubeCollider(glm::vec3(1, 1, 1), glm::vec3(0));
	Texture* wall = aTextureManager->Create("wall", "wall.jpg");
	Mesh* cubeMesh = aMeshManager->Create("Cube", "cube.obj");
	doorColl = aColliderManager->Create("doorColl", cube);
	doorColl->tag = "Wall";
	Door = myObjectManager->Create("Door", cubeMesh, wall, doorColl, NULL);
	Door->Position = glm::vec3(10, 0, 0);
	Door->Scale = glm::vec3(2, 6, 0.5);
	FirstLevels = new Levels();
	
	theObjectManager = myObjectManager;
	player->aShaderManager = aShaderManager;
	theTime = aTime;
}

void MainGameplay::Start() // runs once in the update loop
{ 
	
	
	
}

void MainGameplay::Run() // repeatedly runs in the update loop
{
	player->InputMovement();

	

	if (iSwitch->Collided(player->playerColl) && !MainGameplayRunOnce)
	{
		theObjectManager->Destroy(Door);
		MainGameplayRunOnce = true;
		//std::cout << " switch collided" << std::endl;
	}

	player->CheckCollision();
	
	
	

}
