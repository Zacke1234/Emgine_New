#include "Levels.h"

std::vector<Levels*> Levels::levelList;

Levels::Levels(ShaderManager* aShaderManager)
{
	theShaderManager = aShaderManager;

	levelList.push_back(this);
}

void Levels::Load()
{
	
}
