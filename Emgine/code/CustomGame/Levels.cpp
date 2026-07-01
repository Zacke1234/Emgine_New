#include "Levels.h"

std::vector<Levels*> Levels::levelList;

int Levels::SelectedLevel;

Levels::Levels(ShaderManager* aShaderManager, Time* aTime)
{
	theShaderManager = aShaderManager;
	tempTime = aTime;
	this->levelID += 1;
	levelList.push_back(this);
}

void Levels::Load()
{
	levelTime = tempTime->CurrentTime;
}
