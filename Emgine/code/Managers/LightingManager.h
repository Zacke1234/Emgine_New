#pragma once
#include <Lighting.h>
class LightingManager
{
public: 

	LightData* DefaultLighting;

	LightData* InitDefaultLighting();
	LightData* Create(std::string name = "newLight", Shader* shader = NULL, LightData* light = NULL);
	LightData* InitialiseLightData(Shader* shader, LightData* aLightData);
	void Destroy(Lighting* light, LightData* lightData);
	
	LightData* SetDirectional(LightData* aLightData, Object* test);
	LightData* SetPoint(LightData* aLightData, Object* test = NULL);
	LightData* SetSpot(LightData* aLightData, Object* test);
};

