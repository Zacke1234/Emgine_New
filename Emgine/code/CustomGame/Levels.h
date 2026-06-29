#pragma once
#include <string>
#include <vector>
#include "ObjectManager.h"
#include "ShaderManager.h"
#include "Time/Time.h"

class Levels
{
public:
	Levels(ShaderManager* aShaderManager = NULL, Time* aTime = NULL);

	Time* tempTime;

	static std::vector<Levels*> levelList;

	static int SelectedLevel;

	int levelID = 0;

	float levelTime = 0.0f;

	ShaderManager* theShaderManager;

	std::vector<Object*> ObjectsInLevel;
	//static std::vector<Object*> Entities;
	std::string name = "placeHolder";

	void Load();

};

