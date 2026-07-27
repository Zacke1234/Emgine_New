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
	CubeCollider* cubeColl1 = new CubeCollider(glm::vec3(1), glm::vec3(0));
	CubeCollider* cubeColl2 = new CubeCollider(glm::vec3(1), glm::vec3(0));
	CubeCollider* cubeColl3 = new CubeCollider(glm::vec3(1), glm::vec3(0));
	
	Collider* WallCollider;
	WallCollider = aColliderManager->Create("Wall", cubeColl, false);
	WallCollider->tag = "Wall";

	Collider* PlaneCollider;
	PlaneCollider = aColliderManager->Create("PlaneColl", planeColl, true);

	Texture* wall = aTextureManager->Create("wall", "wall.jpg");
	Texture* defaultTex = aTextureManager->Create("default", "Default 1.png");
	Texture* goalTexture = aTextureManager->Create("goal", "goal.png");
	Texture* platformTexture = aTextureManager->Create("gul", "gul.png");
	//Texture* enemyTexture = aTextureManager->Create("lila", "lila.png");
	Mesh* cubeMesh = aMeshManager->Create("Cube", "cube.obj");
	Mesh* fish = aMeshManager->Create("fish", "fish.obj");

	Wall1 = myObjectManager->Create("Wall_1",
		cubeMesh,
		wall,
		aColliderManager->Create("Wall1", cubeColl1, false),
		NULL
	);

	Wall2 = myObjectManager->Create("Wall_2",
		cubeMesh,
		wall,
		aColliderManager->Create("Wall2", cubeColl2, false),
		NULL
	);

	Wall3 = myObjectManager->Create("Wall_3",
		cubeMesh,
		wall,
		aColliderManager->Create("Wall3", cubeColl3, false),
		NULL
	);

	


	Wall1->Position = glm::vec3(10, 6.3f, 3);
	Wall1->Scale = glm::vec3(2, 6, 0.5);
	Wall1->myCollider->tag = "Wall";

	Wall2->Position = glm::vec3(12.8, 6.3f, 1.4);
	Wall2->Scale = glm::vec3(2, 6, 0.5);
	Wall2->Rotation = glm::vec3(glm::radians(90.0f));
	Wall2->myCollider->tag = "Wall";

	Wall3->Position = glm::vec3(7.3, 6.3f, 1.4);
	Wall3->Scale = glm::vec3(2, 6, 0.5);
	Wall3->Rotation = glm::vec3(glm::radians(90.0f));
	Wall3->myCollider->tag = "Wall";

	
	

	//Mesh* quadplane = myMeshManager->Create("quadplane", "quadplane.obj");
	PlaneObj = myObjectManager->Create("Plane",
		cubeMesh,
		defaultTex,
		planeColl,
		NULL()
	);

	
	myObjectManager->FindAndSetProperties("Plane", glm::vec3(0.0f), glm::vec3(100.0f, 0.5f, 100.0f), glm::vec3(0.0f));

	 Light = myObjectManager->CreateLight("SceneLight",
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
	
	CubeCollider* cube = new CubeCollider(glm::vec3(1, 1, 1), glm::vec3(0));
	
	
	doorColl = aColliderManager->Create("doorColl", cube);
	doorColl->tag = "Wall";
	Door = myObjectManager->Create("Door", cubeMesh, wall, doorColl, NULL);
	Door->Position = glm::vec3(10, 6.3f, 0);
	Door->Scale = glm::vec3(2, 6, 0.5);
	iSwitch->getObject->Position = glm::vec3(3, 1, 3);
	goal->getObject->Position = glm::vec3(10, 1.5f, 1.5);

	Platform = myObjectManager->Create("Box",
		cubeMesh,
		platformTexture,
		aColliderManager->Create("Box", cubeColl3, false),
		NULL
	);

	Platform->Scale = glm::vec3(1, 0.1, 1);
	Platform->Position = glm::vec3(0, 2, 0);
	Platform->myCollider->tag = "Box";

	Level1 = new Levels(aShaderManager, theTime, myObjectManager);
	
	Level1->name = "Level one";

	for (auto& objs : Object::Entities)
	{
		Level1->ObjectsInLevel.push_back(objs);
	}
	
	Level2 = new Levels(aShaderManager, theTime, myObjectManager);

	Level2->name = "Level two";

	

	Level3 = new Levels(aShaderManager, theTime, myObjectManager);

	Level3->name = "Level Three";

	
	Level2->ObjectsInLevel.push_back(player->player);
	Level2->ObjectsInLevel.push_back(Light);
	Level2->ObjectsInLevel.push_back(PlaneObj);
	Level2->ObjectsInLevel.push_back(goal->getObject);
	Level2->ObjectsInLevel.push_back(Platform);

	Level3->ObjectsInLevel.push_back(player->player);
	Level3->ObjectsInLevel.push_back(Light);
	Level3->ObjectsInLevel.push_back(PlaneObj);
	Level3->ObjectsInLevel.push_back(enemy->EnemyObj);
	Level3->ObjectsInLevel.push_back(goal->getObject);
	
	Level1->Init();

	Level2->Init();

	Level3->Init();


	


	
}

void MainGameplay::Start() // runs once in the update loop
{ 
	
	newMenu = new BasicMenus();

	newMenu->ShowMenu(getWindow);
	
	

}
int i = 0;
void MainGameplay::Run() // repeatedly runs in the update loop
{
	player->InputMovement();

	newMenu->RenderMenu();

	enemy->Move();

	Levels::levelList[Levels::SelectedLevel]->GetTime();

	newMenu->getTime = Levels::levelList[Levels::SelectedLevel]->levelTime;

	if (iSwitch->Collided(player->playerColl) && switchColided == false)
	{
		for (Object* object : Object::Entities)
		{
			if (object->namn == Door->namn)
			{
				Object::Entities.erase(Object::Entities.begin() + Door->ObjectID - 1);
				delete(Door);
				doorColl = NULL;
				switchColided = true;
			}
		}
		
		
		
		
		//std::cout << " switch collided" << std::endl;
	}

	if (goal->Collided(player->playerColl))
	{
		bool completed = false;
	
		if (Levels::SelectedLevel == i && !completed)
		{
			GoalColided = true;
			Levels::levelList[i]->isLevelCompleted = true;

			Levels::levelList[i]->recordTime = Levels::levelList[i]->levelTime;
			
			Levels::levelList[i]->Clear();

			
			i++;
			if (i >= 3)
			{
				//std::cout << "you won" << std::endl;
				completed = true;
				return;
			}
			Levels::SelectedLevel++;
			
			
			
			Levels::levelList[i]->Load();

			newMenu->Teleported = true;
		}
	
		
		
	}

	



	player->CheckCollision();
	
	if (newMenu->Teleported)
	{
		player->player->Position = glm::vec3(1, 1, 1);
		newMenu->Teleported = false;
	}

	if (Levels::SelectedLevel == 0 && true) // Level 1
	{
		goal->getObject->Position = glm::vec3(10, 1.5f, 1.5);
		Platform->Position = glm::vec3(0, -10, 0);
		//std::cout << "Level 1" << std::endl;
		//false;
	}

	if (Levels::SelectedLevel == 1 && true) // Level 2
	{
		goal->getObject->Position = glm::vec3(7, 10, 0);
		Platform->Position = glm::vec3(7, 2, 0);
		//std::cout << "Level 2" << std::endl;
		//false;
	}

	if (Levels::SelectedLevel == 2 && true) // Level 3
	{
		goal->getObject->Position = glm::vec3(35, 1.5f, 35);
		Platform->Position = glm::vec3(0, -10, 0);
		//std::cout << "Level 3" << std::endl;
		//false;
	}

}
