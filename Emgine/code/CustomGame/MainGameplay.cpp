#include "MainGameplay.h"



void MainGameplay::Initialise(GLFWwindow* aWindow, ObjectManager* myObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager, CameraManager* aCamManager, Time* aTime, ShaderManager* aShaderManager, Physics* aPhysics, LightingManager* aLightingManager) // runs once when initialising the game
{
	getWindow = aWindow;
	theObjectManager = myObjectManager;
	
	theTime = aTime;

	glm::vec3 extentsPlane = { 100, 0.5f,100 };
	CubeCollider* planeColl;
	planeColl = new CubeCollider(extentsPlane, glm::vec3(0));

	CubeCollider* cubeColl = new CubeCollider(glm::vec3(1), glm::vec3(0));
	
	Collider* WallCollider;
	WallCollider = aColliderManager->Create("Wall", cubeColl, false);
	WallCollider->tag = "Wall";

	Collider* PlaneCollider;
	PlaneCollider = aColliderManager->Create("PlaneColl", planeColl, true);

	Texture* wall = aTextureManager->Create("wall", "wall.jpg");
	Texture* defaultTex = aTextureManager->Create("default", "Default 1.png");
	Texture* goalTexture = aTextureManager->Create("goal", "goal.png");
	Mesh* cubeMesh = aMeshManager->Create("Cube", "cube.obj");
	Mesh* fish = aMeshManager->Create("fish", "fish.obj");

	Wall1 = myObjectManager->Create("Wall",
		cubeMesh,
		wall,
		WallCollider,
		NULL
	);

	Wall1->Position = glm::vec3(10, 6.3f, 3);
	Wall1->Scale = glm::vec3(2, 6, 0.5);

	//Mesh* quadplane = myMeshManager->Create("quadplane", "quadplane.obj");
	PlaneObj = myObjectManager->Create("Plane",
		cubeMesh,
		defaultTex,
		planeColl,
		NULL()
	);

	
	myObjectManager->FindAndSetProperties("Plane", glm::vec3(0.0f), glm::vec3(100.0f, 0.5f, 100.0f), glm::vec3(0.0f));

	myObjectManager->CreateLight("SceneLight",
		NULL,
		NULL,
		NULL,
		aLightingManager->Create("SceneLight", aShaderManager->DefaultShader, aLightingManager->DefaultLighting),
		NULL);

	myObjectManager->FindAndSetProperties("SceneLight", glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.0f));

	iSwitch = new Interactable(myObjectManager, aMeshManager, aTextureManager, aColliderManager, aPhysics);
	player = new Player(getWindow, myObjectManager, aMeshManager, aTextureManager, aColliderManager, aRigidbodyManager, aCamManager, aTime, aPhysics);
	goal = new GoalPost(myObjectManager, aMeshManager, aTextureManager, aColliderManager, aPhysics);
	player->aShaderManager = aShaderManager;

	enemy = new Enemy(myObjectManager, aRigidbodyManager, aColliderManager, aMeshManager, aTextureManager);
	
	SphereCollider* sphere = new SphereCollider(1.0f, glm::vec3(0, 0, 0));
	Collider* doorColl;
	CubeCollider* cube = new CubeCollider(glm::vec3(1, 1, 1), glm::vec3(0));
	
	
	doorColl = aColliderManager->Create("doorColl", cube);
	doorColl->tag = "Wall";
	Door = myObjectManager->Create("Door", cubeMesh, wall, doorColl, NULL);
	Door->Position = glm::vec3(10, 6.3f, 0);
	Door->Scale = glm::vec3(2, 6, 0.5);
	

	TheLevels = new Levels(aShaderManager, theTime, myObjectManager);
	// Wall1 +  player->player + PlaneObj
	TheLevels->ObjectsInLevel.push_back(Door);
	TheLevels->ObjectsInLevel.push_back(player->player);
	TheLevels->ObjectsInLevel.push_back(PlaneObj);
	TheLevels->ObjectsInLevel.push_back(Wall1);
	TheLevels->ObjectsInLevel.push_back(goal->getObject);
	TheLevels->ObjectsInLevel.push_back(enemy->EnemyObj);
	TheLevels->name = "Level one!";
	//TheLevels->ObjectsInLevel = { player->player, iSwitch->getObject, Door, goal->getObject};
	

	iSwitch->getObject->Position = glm::vec3(3, 1, 3);
	goal->getObject->Position = glm::vec3(10, 1.5f, 1.5);

	
}

void MainGameplay::Start() // runs once in the update loop
{ 
	
	newMenu = new BasicMenus();

	newMenu->ShowMenu(getWindow);
	



}

void MainGameplay::Run() // repeatedly runs in the update loop
{
	player->InputMovement();

	newMenu->RenderMenu();

	enemy->Move();

	TheLevels->Load();

	newMenu->getTime = TheLevels->levelTime;

	if (iSwitch->Collided(player->playerColl) && !MainGameplayRunOnce)
	{
		theObjectManager->Destroy(Door);
		MainGameplayRunOnce = true;
		//std::cout << " switch collided" << std::endl;
	}

	if (goal->Collided(player->playerColl))
	{
		TheLevels->isLevelCompleted = true;
		TheLevels->Clear();
	}

	player->CheckCollision();
	
	if (newMenu->Teleported)
	{
		player->player->Position = glm::vec3(1, 1, 1);
		newMenu->Teleported = false;
	}
	

}
