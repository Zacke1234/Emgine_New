#pragma once
#include "Player.h"
#include "Terrain.h"
#include "Levels.h"
#include "Interactable.h"
#include "BasicMenus.h"
#include "Enemy.h"
#include "Managers/ObjectManager.h"

//#include "Physics.h"



class MainGameplay
{
public:
	void Initialise(GLFWwindow* getWindow, ObjectManager* myObjectManager, MeshManager* aMeshManager, TextureManager* aTextureManager, ColliderManager* aColliderManager, RigidbodyManager* aRigidbodyManager, CameraManager* aCamManager, Time* aTime, ShaderManager* aShaderManager, Physics* aPhysics, LightingManager* aLightingManager);
	void Start();
	void Run();

	Collider* doorColl;
	Interactable* iSwitch;
	Player* player;
	GLFWwindow* getWindow;
	ObjectManager* theObjectManager;
	Object* PlaneObj;
	Object* Door;
	Object* Wall1;
	Object* Wall2;
	Object* Wall3;
	Levels* TheLevels;

	Time* theTime;
	BasicMenus* newMenu;
	Enemy* enemy;
	GoalPost* goal;

	bool MainGameplayRunOnce = false;
};

