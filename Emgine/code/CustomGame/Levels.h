#pragma once
#include <string>
#include <vector>
#include "ObjectManager.h"
#include "ShaderManager.h"
#include "Time/Time.h"

class Levels
{
public:
	Levels(ShaderManager* aShaderManager = NULL, Time* aTime = NULL, ObjectManager* myObjectManager = NULL);

	Time* tempTime;

	static std::vector<Levels*> levelList;

	static int SelectedLevel;

	int levelID = 0;

	float levelTime = 0.0f;

	float recordTime = 0.0f;

	bool isLevelCompleted = false;

	bool TimeReset = false;

	ShaderManager* theShaderManager;
	ObjectManager* theObjManager;

	std::vector<Object*> ObjectsInLevel;

	std::vector<glm::vec3> ObjectPositions;

	//static std::vector<Object*> Entities;
	std::string name = "placeHolder";

	void GetTime();

	void Clear();

	void Init();

	void Load();

};

